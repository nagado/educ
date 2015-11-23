#include <fstream>
#include <deque>
#include "compressor.h"
#include "BitCashier.h"
#include "OffsetAndLength.h"
#include <iostream>//


int slide_window(unsigned index, std::deque<Config::Byte>& window, std::ifstream& in)
{
  while (index > window.size() / 2 && window.size() > Config::window_width / 2)
 {
    int input = in.get();

    if (!in.eof() && input >= 0)
    {
      window.push_back(Config::Byte(input));
      window.pop_front();
      --index;
    }
    else
    {
      window.pop_front();
      --index;
    }
  }

  return index;
}

bool find_a_match(const std::deque<Config::Byte>& window, const unsigned i, OffsetAndLength& off_len)
{
  int start = 0;
  bool checking = false;

  for (unsigned k = 0; k < i; ++k)
  {
    if (window[k] == window[i] && !checking)
    {
      checking = true;
      start = k;
    }
    else if (checking == true && (window[k] != window[i + k - start] || k - start == Config::max_match_length))
    {
      checking = false;
      if (unsigned(off_len.get_length()) < k - start)
        off_len.set(i - start, k - start);

      if (off_len.get_length() == Config::max_match_length)
        break;   
  
      k = start + 1;
      start = 0;
    }
    else if (checking == true && ((k + 1 == i && window[k] == window[i + k - start]) || window.size() - 1 == i + k - start))
    {
      checking = false;
      if (unsigned(off_len.get_length()) < k - start + 1)
        off_len.set(i - start, k - start + 1);

      if (off_len.get_length() == Config::max_match_length)
        break;   
  
      k = start + 1;
      start = 0;
    }
  }

  if (off_len.get_length() > 1)
    return true;
  else
    return false;
}

int write_result(bool match_found, std::ofstream& out, std::deque<Config::Byte>& window, unsigned index, OffsetAndLength& off_len, BitCashier& bits)
{
  if (match_found)
  {
    bits.add_bit(true);
    //std::cout << "<" << off_len.get_offset() << "," << off_len.get_length() << ">";//
    bits.add_bits(off_len.get_offset(true));
    bits.add_bits(off_len.get_length(true), Config::encoded_len);
    index += off_len.get_length() - 1;
  }
  else
  {
    bits.add_bit(false);
    //std::cout << char(window[index]);//
    bits.add_bits((window[index]));
  }

  while (bits.size() >= Config::byte_length)
    out.put(bits.pop_bits());

  return index;
}

void handle_decompressed_multibytes(OffsetAndLength& off_len, std::deque<Config::Byte>& window, std::ofstream& out)
{
  for (unsigned i = 0; i < unsigned(off_len.get_length()); ++i)
  {
    assert(window.size() - off_len.get_offset() < window.size() && window.size() - off_len.get_offset() >= 0);    

    unsigned index = window.size() - off_len.get_offset();
    out.put(window[index]);
    window.push_back(window[index]);
  }
}

void write_decompressed_result(BitCashier& bits, std::deque<Config::Byte>& window, std::ofstream& out)
{
  if(bits.read() && bits.size() >= Config::encoded_length)
  {
    bits.pop();

    OffsetAndLength off_len;
    int offs = bits.pop_bits();
    int lens = bits.pop_bits(Config::encoded_len);
    off_len.set(offs, lens, true);

    handle_decompressed_multibytes(off_len, window, out);
  }  
  else if (!bits.read() && bits.size() >= Config::untouched_length)
  {
    bits.pop();
    Config::Byte byte = bits.pop_bits();
    out.put(byte);
    window.push_back(byte);
  }
}

void write_last_byte(BitCashier& bits, std::ofstream& out)
{
  while (bits.size() > 0 && bits.size() < Config::byte_length)
    bits.add_bit(false);

  out.put(bits.pop_bits());
}


void compress(const std::string& filename)
{
  std::ifstream in (filename, std::ios::in|std::ios::binary);
  assert(in);
  std::ofstream out (filename + ".lzw", std::ios::out|std::ios::binary|std::ios::trunc);
  std::deque<Config::Byte> window;
  BitCashier bits;  

  for (unsigned i = 0; i < Config::window_width && !in.eof(); ++i)
  {
    int input = in.get();
    if (input < 0)
      break;

    window.push_back(Config::Byte(input));
  }


  for (unsigned i = 0; i < window.size(); ++i)
  {
    i = slide_window(i, window, in);
    OffsetAndLength off_len;   
    i = write_result(find_a_match(window, i, off_len), out, window, i, off_len, bits);
  }

  if (bits.size() != 0)
    write_last_byte(bits, out);
}

void decompress(const std::string& filename)
{
  std::ifstream in (filename, std::ios::in|std::ios::binary);
  assert(in);
  std::ofstream out (filename.substr(0, filename.length() - 4), std::ios::out|std::ios::binary|std::ios::trunc);
  std::deque<Config::Byte> window;
  BitCashier bits;

  while (!in.eof())
  {
    int input = in.get();
    if (input < 0)
      break;

    bits.add_bits(Config::Byte(input));
    write_decompressed_result(bits, window, out);
    
    while (window.size() > Config::window_width / 2)
      window.pop_front();
  }
}


int main(int argc, char** argv)
{
  if (argc == 2)
    compress(argv[1]);
  else if (argc == 3)
    decompress(argv[1]);

  std::cerr << "Program ended\n";

  exit(0);
}


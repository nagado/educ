#include <fstream>
#include <deque>
#include "compressor.h"
#include "BitCashier.h"
#include "OffsetAndLength.h"
#include <iostream>//

//Make length shorter(32/16 bytes length - 4-5 bites to record)
//let the bits record themselves

int slide_window(int index, std::deque<Byte>& window, std::ifstream& in, std::streampos& end_of_file)
{
  while (index > window.size() / 2 && window.size() > window_width / 2)
 {
    if (in.tellg() < end_of_file)
    {
      window.push_back(in.get());
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

bool find_a_match(std::deque<Byte>& window, int i, OffsetAndLength& off_len)
{
  int start = 0;
  bool checking = false;

  for (int k = 0; k < i; ++k)
  {
    if (window[k] == window[i] && checking == false)
    {
      checking = true;
      start = k;
    }
    else if (checking == true && (window.size() == i + k - start || window[k] != window[i + k - start]))
    {
      checking = false;
      if (off_len.get_length() < k - start)
        off_len.set(i - start, k - start);

      k = start + 1;
      start = 0;
    }
  }

  if (off_len.get_offset() == 0) put_error_and_exit("Offset is impossible\n");//

  if (off_len.get_length() > 1)
    return true;
  else
    return false;
}

void compressor(const std::string& filename)
{
  std::ifstream in (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ofstream out (filename + ".lzw", std::ios::out|std::ios::binary|std::ios::trunc);
  std::streampos end_of_file = in.tellg();
  in.seekg(0, std::ios::beg);

  std::deque<Byte> window;
  BitCashier bits;
  
  for (int i = 0; i < window_width && in.tellg() < end_of_file; ++i)
    window.push_back(in.get());

  for (int i = 0; i < window.size(); ++i)
  {
    i = slide_window(i, window, in, end_of_file);
    OffsetAndLength off_len;

    if (find_a_match(window, i, off_len))
    {
      bits.add(true);
      //std::cout << "<" << off_len.get_offset() << "," << off_len.get_length() << ">";//
      bits.add(off_len.get_offset(true));
      bits.add(off_len.get_length(true));
      i += off_len.get_length() - 1;
    }
    else
    {
      bits.add(false);
      //std::cout << char(window[i]);//
      bits.add((window[i]));
    }

    while (bits.size() >= byte_length)
      out.put(bits.pop_byte());
  }

  while (bits.size() > 0 && bits.size() < 8)
    bits.add(false);

  if (bits.size() == 8)
    out.put(bits.pop_byte());
}

void decompressor(const std::string& filename)
{
  std::ifstream in (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ofstream out (filename.substr(0, filename.length() - 4), std::ios::out|std::ios::binary|std::ios::trunc);
  std::streampos end_of_file = in.tellg();
  in.seekg(0, std::ios::beg);

  std::deque<Byte> window;
  BitCashier bits;

  while (in.tellg() < end_of_file)
  {
    bits.add(Byte(in.get()));
    if(bits.read_not_pop() && bits.size() >= encoded_length)
    {
      bits.pop();
      OffsetAndLength off_len;
      off_len.set_offset(bits.pop_byte(), true);
      off_len.set_length(bits.pop_byte(), true);
      //std::cerr << "<" << off_len.get_offset() << ", " << off_len.get_length() << ">";//

      for (int i = 0; i < off_len.get_length(); ++i)
      {
        int index = window.size() - off_len.get_offset();
        if (index >= window.size() || index < 0) put_error_and_exit("Index is out of range.\n");
        out.put(window[index]);
        window.push_back(window[index]);
      }
    }  
    else if (!bits.read_not_pop() && bits.size() >= untouched_length)
    {
      bits.pop();
      Byte byte = bits.pop_byte();
      //std::cout << char(byte);//
      out.put(byte);
      window.push_back(byte);
    }
    
    while (window.size() > window_width / 2)
      window.pop_front();
  }
}


int main(int argc, char** argv)
{
  if (argc == 2)
    compressor(argv[1]);
  else if (argc == 3)
    decompressor(argv[1]);

  std::cerr << "Program ended\n";

  exit(0);
}


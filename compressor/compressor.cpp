#include <string>
#include <fstream>
#include <deque>
#include <iostream>
#include "Bit_cashier.cpp"
//Solve the issue with weird representation of first bytes in a text file
//
const int window_width = 510;//Won't work if more
const int byte_length = 8;
const int encoded_length = 17;
const int untouched_length = 9;
using Byte = char;


void put_error_and_exit(const std::string& message)
{
  std::cerr << message;
  exit(1);
}

int slide_window(int index, std::deque<Byte>& window, std::ifstream& in, std::streampos& end_of_file)
{
  while (index > window.size() / 2 && window.size() > 255)
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

bool find_a_match(std::deque<Byte>& window, int i, int* offset_and_length)
{
  int start = 0;
  offset_and_length[0] = 0;
  offset_and_length[1] = 0;
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

      if (offset_and_length[1] < k - start)
      {
        offset_and_length[0] = i - start;
        offset_and_length[1] = k - start;
      }

      k = start + 1;
      start = 0;
    }
  }

  if (offset_and_length[1] > 2)
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
  Bit_cashier bits;
  
  for (int i = 0; i < window_width && in.tellg() < end_of_file; ++i)
    window.push_back(in.get());

  for (int i = 0; i < window.size(); ++i)
  {
    i = slide_window(i, window, in, end_of_file);
    int offset_and_length[2];

    if (find_a_match(window, i, offset_and_length))
    {
      bits.add(true);
      bits.add(char(offset_and_length[0]));
      bits.add(char(offset_and_length[1]));
      i += offset_and_length[1] - 1;
    }
    else
    {
      bits.add(false);
      bits.add(window[i]);
    }

    while (bits.size() >= byte_length)
      out.put(bits.pop_byte());
  }

  while (bits.size() > 0 && bits.size() < 8)
    bits.add(false);

  if (bits.size() == 8)
    out.put(bits.pop_byte());
}

int decode_char(char ch)
{
  int res = ch;

  if (res < 0)
    res += 256;

  return res;
}

void decompressor(const std::string& filename)
{
  std::ifstream in (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ofstream out (filename.substr(0, filename.length() - 4), std::ios::out|std::ios::binary|std::ios::trunc);
  std::streampos end_of_file = in.tellg();
  in.seekg(0, std::ios::beg);

  std::deque<Byte> window;
  Bit_cashier bits;
  
  while (in.tellg() < end_of_file)
  {
    bits.add(char(in.get()));
    
    if(bits.read_not_pop() && bits.size() >= encoded_length)
    {
      bits.pop();
      int best_offset = decode_char(bits.pop_byte());
      int best_length = decode_char(bits.pop_byte());
 
      for (int i = 0; i < best_length; ++i)
      {
        out.put(window[window.size() - best_offset]);
        window.push_back(window[window.size() - best_offset]);
      }
    }  
    else if (!bits.read_not_pop() && bits.size() >= untouched_length)
    {
      bits.pop();
      char byte = bits.pop_byte();
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

  exit(0);
}


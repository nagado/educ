#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <random>
#include <sstream>
#include <utility>
#include <iterator>

using Byte = char;
const std::string mark = "<encrypted> meta=";
const size_t mark_length = 17;

//===============//
void put_error(const std::string& error_message)
{
  std::cerr << error_message;
  exit(1);
}

//===============//
void shuffle(std::vector<Byte>& input)
{
  std::default_random_engine gen;

  for (size_t i = 0; i < input.size(); ++i)
  {
    std::uniform_int_distribution<int> dis (i, input.size() - 1);
    std::swap(input[i], input[dis(gen)]);
  } 
}

//===============//
void write_file(const std::string& filename, std::vector<Byte> output, const std::string error_message)
{
  std::ofstream file (filename, std::ios::out|std::ios::binary|std::ios::trunc);
  if (!file.is_open())
    put_error(error_message);
  
  file.write(&output[0], output.size());
}

//===============//
void make_key(const std::string& filename)
{
  std::vector<Byte> input;
  std::ifstream file (filename);
  input.assign(std::istream_iterator<char>(file), std::istream_iterator<char>());
  shuffle(input);
  std::string keyname = filename + ".key";
  write_file(keyname, input, "Couldn't open file to save the result.\n");
}

//=====read_key_position=====//
std::streampos read_key_position(const std::string keyname)
{
  long pos = 0;
  std::ifstream meta (keyname + ".meta");

  if (meta.is_open())
    meta >> pos;

  return pos;
}

//===============//
void record_meta_to_both_files(const long key_starts, const long size_of_file, const std::string keyname, std::ofstream& out)
{
  std::ofstream meta_file (keyname + ".meta", std::ios::out|std::ios::trunc);
  meta_file << key_starts + size_of_file;

  std::string tmp = "<encrypted> meta=" + std::to_string(key_starts) + "\n";
  out.write(tmp.c_str(), tmp.length());
}

//===============//
std::streampos read_meta(std::ifstream& file)
{
  std::string pos;
  std::getline(file, pos);
  if (pos.substr(0, mark_length) != mark)
    put_error("A wrong file was given.\n");

  return std::stol(pos.substr(mark_length, pos.length())); 
}

//===============//
void set_up_for_encrypting(
    std::ofstream& out, const std::string& filename, std::streampos& key_starts, std::ifstream& file,
    const std::string& keyname, std::ifstream& key)
{
  out.open(filename + ".enc", std::ios::out|std::ios::binary);

  key_starts = read_key_position(keyname);
  if ((long)(key.tellg()) - key_starts + 1 < file.tellg())
    put_error("The key needs to be changed. There is not enough data to encrypt file safely.\n");

  record_meta_to_both_files(key_starts, file.tellg(), keyname, out);
  file.seekg(0, std::ios::beg);
}

//===============//
void set_up_for_decrypting(
    std::ofstream& out, const std::string& filename, std::streampos& key_starts, std::ifstream& file)
{
  file.seekg(0, std::ios::beg);
  key_starts = read_meta(file);

  out.open(filename.substr(0, filename.length() - 4), std::ios::out|std::ios::binary);
}

//===============//
void crypting(const std::string& filename, const std::string& keyname, bool encrypt = true)
{
  std::streampos key_starts;
  std::ifstream file (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ifstream key (keyname, std::ios::in|std::ios::binary|std::ios::ate);

  if (!file.is_open() || !key.is_open())
    put_error("Couldn't open input and/or key files.\n");

  std::ofstream out;

  if (encrypt)
    set_up_for_encrypting(out, filename, key_starts, file, keyname, key);
  else
    set_up_for_decrypting(out, filename, key_starts, file);

  key.seekg(key_starts, std::ios::beg);
  if (!out.is_open())
    put_error("Couldn't open output file.\n");

  Byte orig;
  while (file.get(orig))
  {
    Byte code;
    key.get(code);
    Byte res = orig ^ code;

    out.put(res);
  }
}

//===============//
int main(int argc, Byte* argv[])
{
  try
  {
    if (argv[1][0] != '-')
      put_error("A key should go first. For help use key '-h'.\n");

    switch(argv[1][1])
    {
      case 'k':
        make_key(argv[2]);
        break;

      case 'e':
        crypting(argv[2], argv[3]);
        break;

      case 'd':
        crypting(argv[2], argv[3], false);
        break;

      default:
        std::cout << "To make a key use '-k' and provide a file as a base for your key.\nTo encrypt a file use key '-e', provide the file to be encrypted, and lastly a key file.\nTo decode a file use '-d', provide file to be decypted and a key that was used for enryption.\n";
    }
 }
  catch(const std::exception& e)
  {
    put_error("Exception: " + std::string(e.what()) + "\n");  
  }  

  exit(0);
}

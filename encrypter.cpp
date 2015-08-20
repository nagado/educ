#include <iostream>
#include <string.h>
#include <fstream>
#include <ios>
#include <random>
#include <sstream>

using Byte = char;

//=====put_error=====//
void put_error(const std::string& error_message)
{
  std::cout << error_message;
  exit(1);
}

//=====shuffle=====//
void shuffle(std::vector<Byte>& input)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, input.size() - 1);
  int i = 0;

  for (std::vector<Byte>::iterator iter = input.begin(); iter < input.end(); ++i, ++iter)
  {
    int random = distribution(generator);
    Byte tmp = input[i];
    input[i] = input[random];
    input[random] = tmp;
  } 
}

//=====replace_extension=====//
std::string replace_extension(const std::string& filename, const std::string& new_extension)
{
  int i;

  for (i = 0; filename[i] != '.'; ++i);

  ++i;
  if (filename[i] == '.')
    put_error("Oh, snap! Something went wrong.\n");

  std::string new_name = filename.substr(0, i + 1);
  std::string::const_iterator iter = new_extension.begin();

  for (int k = 0; iter < new_extension.end(); ++k, ++i, ++iter)
    new_name[i] = new_extension[k];

  return new_name;
}

//=====read_file=====//
std::vector<Byte> read_file(const std::string& filename, const std::string error_message, std::streampos& size)
{
  std::ifstream file (filename, std::ios::in|std::ios::binary|std::ios::ate);
  size = file.tellg();
  if (!file.is_open())
    put_error(error_message);

  Byte* inp = new Byte[(long int)(size)];
  file.seekg(0, std::ios::beg);
  file.read(inp, size);
  file.close();
  std::vector<Byte> input(inp, inp + size);
  delete inp;

  if (size == 0)
    put_error("Given file is empty\n");

  return std::move(input);
}

//=====write_file=====//
void write_file(const std::string& filename, std::vector<Byte> output, const std::string error_message, const std::streampos& size)
{
  std::ofstream file (filename, std::ios::out|std::ios::binary|std::ios::trunc);
  if (!file.is_open())
    put_error(error_message);
  
  file.write(&output[0], size);
}

//=====make_key=====//
void make_key(const std::string& filename)
{
  std::streampos size;
  std::vector<Byte> input = read_file(filename, "Couldn't access file-base for a key.\n", size);
  shuffle(input);
  std::string keyname = replace_extension(filename, "key");
  write_file(keyname, input, "Couldn't open file to save the result.\n", size);
}

//=====read_key_position=====//
std::streampos read_key_position(const std::string keyname)
{
  long int tmp = 0;
  std::ifstream meta (keyname + ".meta");

  if (meta.is_open())
    meta >> tmp;

  return tmp;
}

//=====record_meta_to_both_files=====//
void record_meta_to_both_files(const long int key_starts, const long int size_of_file, const std::string keyname, std::ofstream& out)
{
  std::ofstream meta_file (keyname + ".meta", std::ios::out|std::ios::trunc);
  meta_file << key_starts + size_of_file;

  std::string tmp = std::to_string(key_starts) + "\n";
  out.write(tmp.c_str(), tmp.length());
}

//=====read_meta=====//
std::streampos read_meta(std::ifstream& file)
{
  std::string tmp;
  std::getline(file, tmp);
  std::streampos key_starts = std::stol (tmp, nullptr);

  return key_starts; 
}

//=====crypting=====//
void crypting(const std::string& filename, const std::string& keyname, bool encrypt = true)
{
  std::streampos key_starts;
  std::ifstream file (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ifstream key (keyname, std::ios::in|std::ios::binary|std::ios::ate);
  if (!file.is_open() || !key.is_open())
  {
    put_error("Couldn't open input and/or key files.\n");
  }
  std::ofstream out;
  if (encrypt)
  {
    out.open(filename + ".enc", std::ios::out|std::ios::binary);
    key_starts = read_key_position(keyname);
    if ((long int)(key.tellg()) - key_starts + 1 < file.tellg())
      put_error("The key needs to be changed. There is not enough data to encrypt file safely.\n");
    record_meta_to_both_files(key_starts, file.tellg(), keyname, out);
    file.seekg(0, std::ios::beg);
  }
  else
  {
    file.seekg(0, std::ios::beg);
    key_starts = read_meta(file);
    out.open(filename.substr(0, filename.length() - 4), std::ios::out|std::ios::binary);
  }
  key.seekg(key_starts, std::ios::beg);
  if (!out.is_open())
    put_error("Couldn't open output file.\n");

  Byte orig;
  while (file.read(&orig, 1))
  {
    Byte code;
    key.read(&code, 1);
    Byte res = orig ^ code;

    out.write(&res, 1);
  }
}

//=====main=====//
int main(int argc, Byte* argv[])
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

#include <iostream>
#include <string.h>
#include <fstream>
#include <ios>
#include <random>
#include <sstream>

template <class Txt>
void put_error(Txt error_message)
{
  std::cout << error_message;
  exit(1);
}

void shuffle(char* array, const std::streampos* size)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, long(*size) - 1);
  
  for (int i = 0; i < *size; ++i)
  {
    int random = distribution(generator);
    char tmp = array[i];
    array[i] = array[random];
    array[random] = tmp;
  } 
}

void change_extension(char* new_name, const char* filename, const char* extension, char* old_extension = nullptr)
{
  int i;

  for (i = 0; filename[i] != '.'; ++i);

  ++i;

  if (old_extension != nullptr)
  { 
    int k;

    for (k = 0; filename[k + i] != 0; ++k)
      old_extension[k] = filename[k + i];

    old_extension[k + 1] = 0;
  }

  if (filename[i] == '.')
    put_error("Oh, snap! something went wrong.\n");

  strncpy(new_name, filename, i + 1);

  for (int k = 0; extension[k] != 0; ++k, ++i)
    new_name[i] = extension[k];

  new_name[i] = 0;
}

char* read_file(const char* filename, const std::string error_message, std::streampos* const size)
{
  std::ifstream file (filename, std::ios::in|std::ios::binary|std::ios::ate);
  if (!file.is_open())
  {
    file.close();
    put_error(error_message);
  }

  *size = file.tellg();
  char* input = new char[*size];
  file.seekg(0, std::ios::beg);
  file.read(input, *size);
  file.close();

  if (size == 0)
    put_error("Given file is empty\n");

  return input;
}

void write_file(const char* filename, const char* output, const std::string error_message, const std::streampos* size)
{
  std::ofstream file (filename, std::ios::out|std::ios::binary|std::ios::trunc);
  if (!file.is_open())
  {
    put_error(error_message);
  }
  
  file.write(output, *size);
}


void make_key(const char* filename)
{
  std::streampos size;
  char* input = read_file(filename, "Couldn't access file-base for a key.\n", &size);
  shuffle(input, &size); 
  char keyname[strlen(filename)];
  change_extension(keyname, filename, "key");
  write_file(keyname, input, "Couldn't open file to save the result.\n", &size);
}

std::streampos handle_meta_enc(
  std::streampos size_of_file, std::streampos size_of_key, const char* keyname,
  std::ofstream& out, const char* extension
)
{
  std::streampos start = 0;
  char key_meta[strlen(keyname) + 1];
  change_extension(key_meta, keyname, "meta");
  std::ifstream meta (key_meta);
  std::string tmp = "0";
  long int itmp = 0;
  if (meta.is_open())
  {
    std::getline(meta, tmp);
    std::stringstream convert(tmp);
    convert >> itmp;
    start = itmp;
  }
  meta.close();
  std::ofstream out_meta (key_meta);
  if ((long int)(size_of_key) - itmp + 1 < size_of_file)
    put_error("The key needs to be changed. There is not enough data to encrypt file safely.\n");

  tmp = tmp + " " + extension + "\n";
  const char* st = tmp.c_str();
  out_meta << itmp + size_of_file;
  out.write(st, tmp.length());

  return start;
}

long int read_meta_dec(std::ifstream& file, char* extension)
{
  long int key_starts = 0;
  std::string meta;
  file.seekg(0, std::ios::beg);
  std::getline(file, meta);
  char starts[meta.length()];
  int i;

  for (i = 0; meta[i] != ' '; ++i)
    starts[i] = meta[i];
  
  starts[++i] = 0;

  for (int k = 0; i < meta.length(); ++i, ++k)
    extension[k] = meta[i];

  extension[++i] = 0;
  std::stringstream convert(starts);
  convert >> key_starts;

  return key_starts;
}


void crypting(const char* filename, const char* keyname, bool encrypt = true)
{
  std::streampos key_starts;
  char extension[10];
  char outname[strlen(filename)];
  std::ifstream file (filename, std::ios::in|std::ios::binary|std::ios::ate);
  std::ifstream key (keyname, std::ios::in|std::ios::binary|std::ios::ate);
  if (!file.is_open() || !key.is_open())
  {
    put_error("Couldn't open input and/or key files.\n");
  }
  std::ofstream out;
  if (encrypt)
  {
    change_extension(outname, filename, "enc", extension);
    out.open(outname, std::ios::out|std::ios::binary);
    key_starts = handle_meta_enc(file.tellg(), key.tellg(), keyname, out, extension);
    file.seekg(0, std::ios::beg);
  }
  else
  {
    file.seekg(0, std::ios::beg);
    key_starts = read_meta_dec(file, extension);
    change_extension (outname, filename, extension);
    out.open(outname, std::ios::out|std::ios::binary);
  }
  key.seekg(key_starts, std::ios::beg);
  if (!out.is_open())
  {
    put_error("Couldn't open output file.\n");
  }

  char orig;
  char code;
  
  while (file.read(&orig, 1))
  {
    key.read(&code, 1);
    char res = orig ^ code;

    out.write(&res, 1);
  }
}

int main(int argc, char* argv[])
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

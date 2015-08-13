#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

string read_file(string& address, string error_message, bool clean = false)
{
  ifstream f;

  f.open(address);
  if(!f)
  {
    cout << error_message;
    f.close();
    exit(1);
  }

  char c;
  string text = "";


  while (f.get(c))
    if ((c != ' ') && (c != '\n') && (c != '.') || clean)
      text += c;

  f.close();

  if (text == "")
  {
    cout << "Given file is empty";
    exit(1);
  }

  return text;
}

void record_file(string& address, string& text)
{
  ofstream f;
  f.open(address);
  f << text;
  f.close();
}

string encrypt(string& text, string& key)
{
  int shift = rand() % 100;
  cout << shift << " " << char(shift) << endl;

  for (int i = 0; i < text.length(); i++)
    text[i] = text[i] ^ key[(i + shift) % key.length()];

  text = char(shift) + text;

  return text;
}

string decrypt(string& text, string& key)
{
  int shift = text[0];
  cout << shift << " " << char(shift) << endl;
  text = text.substr(1, text.length());

  for (int i = 0; i < text.length(); i++)
    text[i] = text[i] ^ key[(i + shift) % key.length()];

  return text;
}

string shuffle(string& str)
{
  char tmp;
  int random;

  for (int i = 0; i < str.length(); i++)
  {
    random = rand() % str.length();
    tmp = str[i];
    str[i] = str[random];
    str[random] = tmp;
  }
    
  return str;
}

void create_key(string& address)
{
  string key_base = read_file(address, "No file found. Provide file name in parameters.\n", true);
  key_base = shuffle(key_base);
  
  ofstream key;
  key.open("key.eck");
  key << key_base;
  key.close();
}

void encrypt_file(string& address)
{
  string text = read_file(address, "No file found. Provide file name for the document you want to encrypt.\n");
  cout << "Create password. Be aware that you can't use spaces: ";
  string password = "", key_address = "key.eck";
  cin >> password;

  string key = read_file(key_address, "No key found. Provide one or make a new one.\n");
  text = encrypt(text, password);
  text = encrypt(text, key);
  record_file(address, text);
  cout << "Your file is encrypted. Please remember your password and keep your key file. Without them you will not able to decrypt your information.\n";
}

void decrypt_file(string& address)
{
  string text = read_file(address, "No file found. Provide a file that you want to decrypt.\n");
  string password = "", key_address = "key.eck";
  cout << "Password: ";
  cin >> password;
  string key = read_file(key_address, "No key found. The key that was used when encrypting should be in the same foulder as the program.\n");
  text = decrypt(text, key);
  text = decrypt(text, password);
  record_file(address, text);
  cout << "Your file is decrypted.\n";
}


int main(int argc, char* argv[])
{
  string address = "";
  char parameter;

  for (int i = 1; i < argc; i++)
  {
    if (regex_match(argv[i], regex("(.*).txt)") ))
    {
      address = argv[i];
      break;
    }
    else if (regex_match(argv[i], regex("-.")))
      parameter = argv[i][1];
  }

  if (address == "")
  {
    cout << "No address was given\n";
    exit(1);
  }

  switch (parameter)
  {
    case 'k':
      create_key(address);
      break;
    case 'e':
      encrypt_file(address);
      break;
    case 'd':
      decrypt_file(address);
      break;
    default:
      cout << "To encrypt your file you need to make a key first. Provide parameter '-k' and a file with any text as a base for the key.\n\nTo encrypt your file when you have a key you need to provide parameter '-e' and a file to be encrypted\n\nTo decrypt a file you need to provide parameter '-d' and a file to be decrypted. The key that was used for encryption should be in the same founder as the program itself, and it should be called 'key.eck'\n";
  }

  return 0;
}


#ifndef TEXTEXCEPTION_H
#define TEXTEXCEPTION_H

#include <string>


class TextException : public std::exception
{
  std::string message;
  
public:
  TextException(std::string text) { message = text; }

  inline const char* what() { return message.c_str(); }
};

#endif

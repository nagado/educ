#include <iostream>


void put_error_and_exit(const std::string& message)
{
  std::cerr << message;
  exit(1);
}

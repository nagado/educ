#include <iostream>
#include "compressor.h"


void Config::put_error_and_exit(const std::string& message)
{
  std::cerr << message;
  exit(1);
}

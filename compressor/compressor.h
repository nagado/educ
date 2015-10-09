#include <cstdint>
#include <assert.h>

namespace Config
{
  const int window_width = 512,
  byte_length = 8,
  encoded_off = 8,
  encoded_len = 4,
  encoded_length = 1 + encoded_off + encoded_len,
  untouched_length = 9,
  max_match_length = 16;
  using Byte = unsigned int8_t;

  void put_error_and_exit(const std::string&);
}


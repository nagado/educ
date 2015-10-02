#include <cstdint>

const int window_width = 512;//Won't work if more
const int byte_length = 8;
const int encoded_off = 8;
const int encoded_len = 4;
const int encoded_length = 1 + encoded_off + encoded_len;
const int untouched_length = 9;
const int max_match_length = 16;
using Byte = unsigned int8_t;


void put_error_and_exit(const std::string&);

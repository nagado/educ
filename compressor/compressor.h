#include <cstdint>

const int window_width = 512;//Won't work if more
const int byte_length = 8;
const int encoded_length = 17;
const int untouched_length = 9;
using Byte = unsigned int8_t;


void put_error_and_exit(const std::string&);

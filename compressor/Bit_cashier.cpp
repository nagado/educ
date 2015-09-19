#include <iostream>
#include <deque>
#include <string>

class Bit_cashier
{
  std::deque<bool> bits;
  const int byte_length = 8;

  void put_error_and_exit(const std::string& message)
  {
    std::cerr << message;
    exit(1);
  }

public:
  Bit_cashier(){}

  void add(const bool new_value)
  {
    bits.push_back(new_value);
  }

  void add(const char future_bits)  
  {
    for (int i = byte_length - 1; i >= 0; --i)
      bits.push_back(bool(future_bits & (1 << i)));
  }   
  
  int size()
  {
    return bits.size();
  }

  bool read_not_pop()
  {
    if (bits.size() < 1)
      put_error_and_exit("No bits left in Bit_cashier.\n");
    
    return bits.front();
  }

  bool pop() 
  {
    if (bits.size() < 1)
      put_error_and_exit("No bits left in Bit_cashier.\n");
  
    bool result;
    result = bits.front();
    bits.pop_front();

    return result;
  
  }

  char pop_byte()
  {
    char byte = 0;

    for(int i = byte_length - 1; i >= 0; --i)
      byte = byte | (pop() << i);

    return byte;
  }
};

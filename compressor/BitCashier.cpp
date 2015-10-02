#include <iostream>
#include <deque>
#include "compressor.h"
#include "BitCashier.h"

void BitCashier::add(const bool new_value)
{
  bits.push_back(new_value);
}

void BitCashier::add(const Byte future_bits)  
{
  for (int i = byte_length - 1; i >= 0; --i)
    bits.push_back(bool(future_bits & (1 << i)));
}   
  
int BitCashier::size()
{
  return bits.size();
}

bool BitCashier::read_not_pop()
{
  if (bits.size() < 1)
    put_error_and_exit("No bits left in Bit_cashier.\n");
    
  return bits.front();
}

bool BitCashier::pop() 
{
  if (bits.size() < 1)
    put_error_and_exit("No bits left in Bit_cashier.\n");

  bool result;
  result = bits.front();
  bits.pop_front();

  return result;
}

Byte BitCashier::pop_byte()
{
  Byte byte = 0;

  for(int i = byte_length - 1; i >= 0; --i)
    byte = byte | (pop() << i);

  return byte;
}

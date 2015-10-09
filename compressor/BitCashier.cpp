#include <iostream>
#include <deque>
#include "compressor.h"
#include "BitCashier.h"


void BitCashier::add_bit(bool new_value)
{
  bits.push_back(new_value);
}

void BitCashier::add_bits(const int future_bits, int num)  
{
  for (int i = num - 1; i >= 0; --i)
    bits.push_back(bool(future_bits & (1 << i)));
}   
  
int BitCashier::size()
{
  return bits.size();
}

bool BitCashier::read()
{
  assert(bits.size() >= 1);
    
  return bits.front();
}

bool BitCashier::pop() 
{
  assert(bits.size() >= 1);

  bool result;
  result = bits.front();
  bits.pop_front();

  return result;
}

int BitCashier::pop_bits(const int bits)
{
  assert(bits > 0 && bits <= 32);
  int result = 0;

  for (int i = bits - 1; i >= 0; --i)
    result = result | (pop() << i);

  return result;
}

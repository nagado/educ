#include <iostream>
#include "compressor.h"
#include "OffsetAndLength.h"


void OffsetAndLength::set(int offs, int len, bool compressed)
{
  assert((!compressed && offs >= 1 && offs <= 256) || (compressed && offs >= 0 && offs <= 255));
  assert((!compressed && len >= 1 && len <= Config::max_match_length) || (compressed && len >= 0 && len <= Config::max_match_length - 1));

  if (compressed)
  {
    offset = offs;
    length = len;
  }
  else
  {
    offset = offs - 1; 
    length = len - 1;
  }
}

Config::Byte OffsetAndLength::get_offset(bool compressed)
{
  assert(compressed); 

  return offset;
}

Config::Byte OffsetAndLength::get_length(bool compressed)
{
  assert(compressed);

  return length;
}


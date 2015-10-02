#include <iostream>
#include "compressor.h"
#include "OffsetAndLength.h"


void OffsetAndLength::set(int offs, int len, bool compressed)
{
  set_offset(offs, compressed);
  set_length(len, compressed);
}

void OffsetAndLength::set_offset(int offs, bool compressed) 
{ 
  if ((!compressed && (offs < 1 || offs > 256)) || (compressed && (offs < 0 || offs > 255)))
    put_error_and_exit("There is no offset that is beyond [1, 256].\n");

  if (compressed)
    offset = offs;
  else
    offset = offs - 1; 
}

void OffsetAndLength::set_length(int len, bool compressed) 
{
  if ((!compressed && (len < 1 || len > max_match_length)) || (compressed && (len < 0 || len > max_match_length - 1)))
    put_error_and_exit("There is no length that is beyond [1, 16].\n");

  if (compressed)
    length = len;
  else
    length = len - 1;
}

Byte OffsetAndLength::get_offset(bool compressed)
{
  if (!compressed)
    put_error_and_exit("Incorrect use of get_length()\n"); 

  return offset;
}
 
int OffsetAndLength::get_offset()
{
  return int(offset) + 1;
}

Byte OffsetAndLength::get_length(bool compressed)
{
  if (!compressed)
    put_error_and_exit("Incorrect use of get_length()\n"); 

  return length;
}

int OffsetAndLength::get_length()
{
  return int(length) + 1; 
}

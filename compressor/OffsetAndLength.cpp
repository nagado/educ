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
  if ((!compressed && (len < 1 || len > 256)) || (compressed && (len < 0 || len > 255)))
    put_error_and_exit("There is no length that is beyond [1, 256].\n");

  if (compressed)
    length = len;
  else
    length = len - 1;
}

Byte OffsetAndLength::get_offset(bool compressed)
{
  if (compressed)
    return offset;
  else
    put_error_and_exit("Incorrect use of get_length()\n"); 
}
 
int OffsetAndLength::get_offset()
{
  return int(offset) + 1;
}

Byte OffsetAndLength::get_length(bool compressed)
{
  if (compressed)
    return length;
  else
    put_error_and_exit("Incorrect use of get_length()\n"); 
}

int OffsetAndLength::get_length()
{
  return int(length) + 1; 
}

class OffsetAndLength{
  Byte offset;
  Byte length;

public:
  OffsetAndLength(){ offset = 0; length = 0;}

  void set(int offs, int len, bool compressed = false);
  void set_offset(int offs, bool compressed = false);
  void set_length(int len, bool compressed = false);
  Byte get_offset(bool compressed);
  int get_offset();
  Byte get_length(bool compressed);
  int get_length();
};

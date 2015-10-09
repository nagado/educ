class OffsetAndLength{
  Config::Byte offset;
  Config::Byte length;

public:
  OffsetAndLength(){ offset = 0; length = 0;}

  void set(int offs, int len, bool compressed = false);
  Config::Byte get_offset(bool compressed);
  inline int get_offset() { return int(offset) + 1; } 
  Config::Byte get_length(bool compressed);
  inline int get_length() { return int(length) + 1; };
};

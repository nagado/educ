class BitCashier
{
  std::deque<bool> bits;
  const int byte_length = 8;

public:
  BitCashier(){}

  void add(const bool);
  void add(const Byte);
  int size();
  bool read_not_pop();
  bool pop();
  Byte pop_byte();
};

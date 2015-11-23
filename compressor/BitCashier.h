class BitCashier
{
  std::deque<bool> bits;

public:
  BitCashier(){}

  void add_bit(bool);
  void add_bits(const int, int num = 8);
  int size();
  bool read();
  bool pop();
  int pop_bits(const int bits = 8);
};

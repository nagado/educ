class BitCashier
{
  std::deque<bool> bits;

public:
  BitCashier(){}

  void add(const bool);
  void add(const int, int num = 8);
  int size();
  bool read_not_pop();
  bool pop();
  int pop_bits(const int bits = 8);
};

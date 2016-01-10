#ifndef RACQUET_H
#define RACQUET_H

#include "Thing.h"
#include <time.h>


class Racquet : public Thing
{
  int length;
  int height;
  int old_x;
  int old_y;

  std::clock_t old_time;

public:
  Racquet() : Thing(false) {}

  void setDimentions(int l, int h) { length = l; height = h; }
  sf::Vector2f getDimentions() const { return sf::Vector2f(length, height); }
  void changePosition(int xx, int yy) override;
  void updatePosition(const sf::RenderWindow& window);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::vector<std::vector<int>> getBorders() const override;

  ~Racquet() override {};
};

#endif

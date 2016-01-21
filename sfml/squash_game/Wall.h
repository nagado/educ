#ifndef WALL_H
#define WALL_H

#include "Thing.h"


class Wall : public Thing
{
  int length;
  int height;

public:
  Wall(int x, int y, int len, int hei) : Thing(false, false), length(len), height(hei) { setPosition(x, y); }

  void changePosition(int xx, int yy) override { setPosition(xx, yy); }
  void setDimentions(int l, int h) { length = l; height = h; }
  sf::Vector2f getDimentions() const { return sf::Vector2f(length, height); }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::vector<std::vector<int>> getBorders() const override;

  ~Wall() override {};
};


#endif

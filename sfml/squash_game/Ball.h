#ifndef BALL_H
#define BALL_H

#include "Thing.h"
#include "Racquet.h" 


class Ball : public Thing
{
  double x;
  double y;
  int radius;

public:
  Ball() : Thing() {}
  Ball(int xx, int yy, int rad, double ang, double spe);
  ~Ball() override {};

  void updatePosition() override;
  
  void setRadius(int r) { radius = r; }
  int getRadius() { return radius; }
  void changePosition(int xx, int yy) override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::vector<std::vector<int>> getBorders() const override;
};

#endif

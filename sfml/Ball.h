#ifndef BALL_H
#define BALL_H

#include "Thing.h"


class Ball : public Thing
{
  int radius;

public:
  Ball() : Thing(true) {};

  void updatePosition();
  inline void setRadius(int r) { radius = r; }
  inline int getRadius() { return radius; }
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  

private:
  void move();
  void recalculateAngle(const Thing& obj);
};

#endif

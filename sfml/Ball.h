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
  Ball() : Thing(true) {};

  void updatePosition(const Racquet& racquet);
  inline void setRadius(int r) { radius = r; }
  inline int getRadius() { return radius; }
  virtual void changePosition(int xx, int yy);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  

private:
  void move();
  void recalculateAngle(const Racquet& racquet);
  bool racquetZone_x(const Racquet& racquet);
  bool racquetZone_y(const Racquet& racquet);
  double balanceAngle(double a);
};

#endif

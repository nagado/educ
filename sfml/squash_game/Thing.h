#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <time.h>


class Thing : public sf::Shape 
{
protected:
  bool movable;
  double speed;
  double angle;

  Thing(bool mov) { movable = mov; }

public:
  virtual void changePosition(int xx, int yy) { setPosition(xx, yy); };
  bool isMovable() const { return movable; }
  void setMovable(bool mov) { movable = mov; }
  virtual unsigned getPointCount() const { return unsigned(1); }
  virtual sf::Vector2f getPoint(unsigned index) const {return sf::Vector2f(1, 2); }
  void setAngle(double a) { angle = a; }
  double getAngle() const { return angle; }
  void setSpeed(double s) { speed = s; }
  double getSpeed() const { return speed; }
  virtual void draw(sf::RenderTarget& target) const {};

  ~Thing() {}
};

#endif

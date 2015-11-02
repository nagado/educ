#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <time.h>


class Thing : public sf::Shape 
{
protected:
  double x;
  double y;
  bool movable;
  double speed;
  double angle;

  Thing(bool mov) { movable = mov; }

public:
  //inline virtual void updatePosition();
  virtual void changePosition(int xx, int yy);
  inline bool isMovable() { return movable; }
  inline void setMovable(bool mov) { movable = mov; }
  virtual unsigned getPointCount() const { return unsigned(1); }
  virtual sf::Vector2f getPoint(unsigned index) const {return sf::Vector2f(1, 2); }
  inline void setAngle(double a) { angle = a; }
  inline double getAngle() { return angle; }
  inline void setSpeed(double s) { speed = s; }
  inline double getSpeed() { return speed; }
  virtual void draw(sf::RenderTarget& target) const {};
  void checkPosition();

  ~Thing() {}
};

#endif

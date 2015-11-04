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
  //inline virtual void updatePosition();
  inline virtual void changePosition(int xx, int yy) { setPosition(xx, yy); };
  inline bool isMovable() const { return movable; }
  inline void setMovable(bool mov) { movable = mov; }
  virtual unsigned getPointCount() const { return unsigned(1); }
  virtual sf::Vector2f getPoint(unsigned index) const {return sf::Vector2f(1, 2); }
  inline void setAngle(double a) { angle = a; }
  inline double getAngle() const { return angle; }
  inline void setSpeed(double s) { speed = s; }
  inline double getSpeed() const { return speed; }
  virtual void draw(sf::RenderTarget& target) const {};

  ~Thing() {}
};

#endif

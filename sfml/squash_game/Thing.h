#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <time.h>


class Thing : public sf::Shape 
{
protected:
  double speed;
  double angle;

  Thing() {}
  Thing(double ang, double spe) : speed(spe), angle(ang) {}

public:
  virtual ~Thing() {}


  virtual void changePosition(int xx, int yy) { setPosition(xx, yy); };
  virtual void updatePosition() {}
  virtual void updatePosition(int mouse_x) {}

  void setAngle(double a) { angle = a; }
  double getAngle() const { return angle; }

  void setSpeed(double s) { speed = s; }
  double getSpeed() const { return speed; }


  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
  virtual std::vector<std::vector<int>> getBorders() const = 0;
  unsigned getPointCount() const override { return unsigned(1); }
  sf::Vector2f getPoint(unsigned index) const override{return sf::Vector2f(1, 2); }
};

#endif

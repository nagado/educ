#ifndef THING_H
#define THING_H

#include <SFML/Graphics.hpp>
#include <time.h>


class Thing : public sf::Shape 
{
protected:
  bool movable;
  bool needs_updating;
  double speed;
  double angle;

  Thing(bool mov, bool upd) : movable(mov), needs_updating(upd) {}
  Thing(bool mov, bool upd, double ang, double spe) : movable(mov), needs_updating(upd), speed(spe), angle(ang) {}

public:
  virtual ~Thing() {}


  virtual void changePosition(int xx, int yy) { setPosition(xx, yy); };
  virtual void updatePosition(const std::vector<std::vector<int>> thing_borders = {}, 
                              const int thing_speed = 0, const double thing_angle = 0) {}
  virtual void updatePosition(int mouse_x) {}

  bool isMovable() const { return movable; }
  void setMovable(bool mov) { movable = mov; }

  bool needsUpdating() { return needs_updating; }
  void setNeedsUpdating(bool upd) { needs_updating = upd; }

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

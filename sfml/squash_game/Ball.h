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
  Ball(int xx, int yy, int rad, double ang, double spe);
  ~Ball() override {};

  void updatePosition(const std::vector<std::vector<int>> thing_borders = {}, 
                      const int thing_speed = 0, const double thing_angle = 0) override;
  
  void setRadius(int r) { radius = r; }
  int getRadius() { return radius; }
  void changePosition(int xx, int yy) override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  std::vector<std::vector<int>> getBorders() const override;

private:
  void recalculateAngle(const std::vector<std::vector<int>> thing_borders = std::vector<std::vector<int>>(),
                        const int thing_speed = 0, const double thing_angle = 0);
  double balanceAngle(double a);
  void move();
};

#endif

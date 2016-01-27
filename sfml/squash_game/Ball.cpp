#include <SFML/Graphics.hpp>
#include "Racquet.h"
#include <type_traits>
#include "Utils.h"
#include <math.h>
#include "Ball.h"


Ball::Ball(int xx, int yy, int rad, double ang, double spe) : Thing(true, true, ang, spe), radius(rad) 
{
  setPosition(xx, yy);
  x = xx;
  y = yy; 
}


void Ball::move()
{
  std::static_assert(angle < 2 * Utils::Pi && angle > 0 * Utils::Pi, "Unacceptable angle\n");

  x += speed * cos(angle);
  y -= speed * sin(angle);
  setPosition(round(x), round(y));
}

void Ball::changePosition(int xx, int yy)
{
  setPosition(xx, yy);
  x = xx;
  y = yy;
}

void Ball::updatePosition(const std::vector<std::vector<int>> thing_borders, const int thing_speed, const double thing_angle)
{
  if (thing_borders.size() != 0) 
    recalculateAngle(thing_borders, thing_speed, thing_angle);
  move();
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int xx = 0;
  int yy = radius;

  std::vector<sf::Vertex> vertices;
  const int vars_count = 4;
  int vars[vars_count][2] {{0, radius}, {0, -radius}, { -radius, 0}, {radius, 0}};

  for (int i = 0; i < vars_count; i++)
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + vars[i][0], round(y) + vars[i][1])));

  while(xx < yy)
  {
    if(f >= 0) 
    { 
      yy--; 
      ddF_y += 2; 
      f += ddF_y; 
    }
 
    xx++; 
    ddF_x += 2; 
    f += ddF_x; 

    const int vars2_count = 8;
    int vars2[vars2_count][2] {{int(round(x)) + xx, int(round(y)) + yy}, {int(round(x)) - xx, int(round(y)) + yy}, 
                               {int(round(x)) + xx, int(round(y)) - yy}, {int(round(x)) - xx, int(round(y)) - yy},
                               {int(round(x)) + yy, int(round(y)) + xx}, {int(round(x)) - yy, int(round(y)) + xx}, 
                               {int(round(x)) + yy, int(round(y)) - xx}, {int(round(x)) - yy, int(round(y)) - xx}};

    for (int i = 0; i < vars2_count; i++)
      vertices.push_back(sf::Vertex(sf::Vector2f(vars2[i][0], vars2[i][1])));
  }

  target.draw(&vertices[0], vertices.size(), sf::TrianglesFan);
}

double Ball::balanceAngle(double a)
{
  a = a - 2 * Utils::Pi * int(a / (2 * Utils::Pi));

  if (a < 0)
    a += 2 * Utils::Pi;

  return a;
}

std::vector<std::vector<int>> Ball::getBorders() const
{
  std::vector<std::vector<int>> borders {{int(getPosition().x) - radius, int(getPosition().y) - radius}, 
                                         {int(getPosition().x) + radius, int(getPosition().y) + radius}};

  return borders;
}


void Ball::recalculateAngle(const std::vector<std::vector<int>> thing_borders, const int thing_speed, const double thing_angle)
{ 
  int start1 [] {thing_borders[0][0], thing_borders[0][1]};
  int endOf1 [] {thing_borders[1][0], thing_borders[1][1]};
    
  if (getPosition().y <= start1[1])
  {
    angle = 2 * Utils::Pi - angle;
    
    if (angle != thing_angle && thing_speed != 0)
    {
      double side = 0;
      
      if (thing_angle == 0)
      {
        side = sqrt(speed * speed + thing_speed * thing_speed - 2 * speed * thing_speed * cos(Utils::Pi - angle));
        angle = acos((side * side + thing_speed * thing_speed - speed * speed) / (2 * side * thing_speed));
      }
      else
      {
        side = sqrt(speed * speed + thing_speed * thing_speed - 2 * speed * thing_speed * cos(angle));
        angle = Utils::Pi - acos((side * side + thing_speed * thing_speed - speed * speed) / (2 * side * thing_speed));
      }

      std::static_assert(side > 0, "Side calculations are uncorrect\n");

      if (angle == 0)
        angle = 0.1 * Utils::Pi;

      if (angle == Utils::Pi)
        angle = 0.9 * Utils::Pi;
    }
  }

  else if (getPosition().y >= endOf1[1] and angle <= Utils::Pi)
      angle = 2 * Utils::Pi - angle; 

  else
    angle = balanceAngle(1 * Utils::Pi - angle);


   if (angle == 0)
     angle = 1.1 * Utils::Pi;

   if (angle == Utils::Pi)
     angle = 1.9 * Utils::Pi;
}

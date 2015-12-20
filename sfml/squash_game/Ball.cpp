#include <SFML/Graphics.hpp>
#include "Racquet.h"
#include "TextException.h"
#include "Utils.h"
#include <math.h>
#include "Ball.h"

void Ball::move()
{
  if (angle > 2 * Utils::PI || angle < 0 * Utils::PI)
    throw TextException("Unacceptable angle\n");

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

void Ball::updatePosition(const Racquet& racquet)
{
  recalculateAngle(racquet);
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

  std::vector<std::vector<int>> vars_list {{0, radius}, {0, -radius}, { -radius, 0}, {radius, 0}};

  for (std::vector<int> vars : vars_list)
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + vars[0], round(y) + vars[1])));

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

    std::vector<std::vector<int>> vars_list2 {{int(round(x)) + xx, int(round(y)) + yy}, {int(round(x)) - xx, int(round(y)) + yy}, 
                                              {int(round(x)) + xx, int(round(y)) - yy}, {int(round(x)) - xx, int(round(y)) - yy},
                                              {int(round(x)) + yy, int(round(y)) + xx}, {int(round(x)) - yy, int(round(y)) + xx}, 
                                              {int(round(x)) + yy, int(round(y)) - xx}, {int(round(x)) - yy, int(round(y)) - xx}};

    for (std::vector<int> vars2 : vars_list2)
      vertices.push_back(sf::Vertex(sf::Vector2f(vars2[0], vars2[1])));
  }

  target.draw(&vertices[0], vertices.size(), sf::TrianglesFan);
}

bool Ball::racquetZone_x(const Racquet& racquet)
{
  int nozone_racquet_left = racquet.getPosition().x - racquet.getDimentions().x / 2 - radius;
  int nozone_racquet_right = racquet.getPosition().x + racquet.getDimentions().x / 2 + radius;

  if (getPosition().x >= nozone_racquet_left && getPosition().x <= nozone_racquet_right)
    return true;
  else
    return false; 
  
}

bool Ball::racquetZone_y(const Racquet& racquet)
{
  if (getPosition().y > Utils::nozone_catchline - int(speed) && getPosition().y <= Utils::nozone_catchline)
    return true;
  else
    return false;  
}

double Ball::balanceAngle(double a)
{
  a = a - 2 * Utils::PI * int(a / (2 * Utils::PI));

  if (a < 0)
    a += 2 * Utils::PI;

  return a;
}

void Ball::recalculateAngle(const Racquet& racquet)
{
  if (getPosition().y <= Utils::nozone_top)
    angle = 2 * Utils::PI - angle; 

  else if (getPosition().x <= Utils::nozone_left || getPosition().x >= Utils::nozone_right)
    angle = balanceAngle(1 * Utils::PI - angle);

  else if (racquetZone_y(racquet) && racquetZone_x(racquet))
  {
    angle = 2 * Utils::PI - angle;
    
    if (angle != racquet.getAngle() && racquet.getSpeed() != 0)
    {
      double side = 0;
      
      if (racquet.getAngle() == 0)
      {
        side = sqrt(speed * speed + racquet.getSpeed() * racquet.getSpeed() - 2 * speed * racquet.getSpeed() * cos(Utils::PI - angle));
        angle = acos((side * side + racquet.getSpeed() * racquet.getSpeed() - speed * speed) / (2 * side * racquet.getSpeed()));
      }
      else
      {
        side = sqrt(speed * speed + racquet.getSpeed() * racquet.getSpeed() - 2 * speed * racquet.getSpeed() * cos(angle));
        angle = Utils::PI - acos((side * side + racquet.getSpeed() * racquet.getSpeed() - speed * speed) / (2 * side * racquet.getSpeed()));
      }

      if (side <= 0)
        throw TextException("Side calculations are wrong\n");

      if (angle == 0)
        angle = 0.2 * Utils::PI;

      if (angle == Utils::PI)
        angle = 0.8 * Utils::PI;   
    }
  }
}

#include <SFML/Graphics.hpp>
#include "Racquet.h"
#include <type_traits>
#include "Utils.h"
#include <math.h>
#include "Ball.h"


Ball::Ball(int xx, int yy, int rad, double ang, double spe) : Thing(ang, spe), radius(rad) 
{
  setPosition(xx, yy);
  x = xx;
  y = yy; 
}


void Ball::changePosition(int xx, int yy)
{
  setPosition(xx, yy);
  x = xx;
  y = yy;
}

void Ball::updatePosition()
{
  x += speed * cos(angle);
  y -= speed * sin(angle);
  setPosition(round(x), round(y));
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

std::vector<std::vector<int>> Ball::getBorders() const
{
  std::vector<std::vector<int>> borders {{int(getPosition().x) - radius, int(getPosition().y) - radius}, 
                                         {int(getPosition().x) + radius, int(getPosition().y) + radius}};

  return borders;
}

#include <SFML/Graphics.hpp>
#include "Thing.h"
#include "TextException.h"
#include <cmath>
#include "Ball.h"
#include <iostream>//


void Ball::move()
{
  if (angle > 2 || angle < 0)
    throw TextException("Unacceptable angle");

  x += speed * cos(angle);
  y += speed * sin(angle);
  setPosition(round(x), round(y));
}

void Ball::updatePosition()
{
  checkPosition();
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

  vertices.push_back(sf::Vertex(sf::Vector2f(round(x), round(y) + radius)));
  vertices.push_back(sf::Vertex(sf::Vector2f(round(x), round(y) - radius)));
  vertices.push_back(sf::Vertex(sf::Vector2f(round(x) - radius, round(y))));  
  vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + radius, round(y))));

  while(xx < yy)
  {
  // ddF_x == 2 * xx + 1; 
  // ddF_y == -2 * yy; 
  // f == xx * xx + yy * yy - radius * radius + 2 * x - y + 1; 

    if(f >= 0) 
    { 
      yy--; 
      ddF_y += 2; 
      f += ddF_y; 
    }
 
    xx++; 
    ddF_x += 2; 
    f += ddF_x; 

    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + xx, round(y) + yy)));
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) - xx, round(y) + yy)));
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + xx, round(y) - yy)));  
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) - xx, round(y) - yy)));
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + yy, round(y) + xx)));
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) - yy, round(y) + xx)));
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) + yy, round(y) - xx)));  
    vertices.push_back(sf::Vertex(sf::Vector2f(round(x) - yy, round(y) - xx)));

  
  }

  target.draw(&vertices[0], vertices.size(), sf::TrianglesFan);
}

//void Ball::recalculateAngle(const Thing& obj)
//{
  //worry about the objects' angleness some time later
     
//}

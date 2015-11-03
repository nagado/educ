#include <SFML/Graphics.hpp>
#include "Racquet.h"
#include "Thing.h"
#include "Utils.h"
#include <ctime>
#include <cmath>


void Racquet::changePosition(int xx, int yy)
{
  angle = 0;
  speed = 0;
  old_x = xx;
  old_y = yy;
  old_time = std::clock();
  setPosition(xx, yy);
}

void Racquet::updatePosition(const sf::RenderWindow& window)
{
  if (getPosition().x - old_x == 0)
  {
    angle = 0;
    speed = 0;
  }
  else 
  {
    if (getPosition().x - old_x > 0)
      angle = 0;
    else
      angle = 1;
  
    speed = abs(getPosition().x - old_x) / (std::clock() - old_time);
  }

  old_x = getPosition().x;
  old_y = getPosition().y;

  int new_x = sf::Mouse::getPosition(window).x;
  
  if (not (new_x < length / 2 || new_x > Utils::window_x - length / 2)) //left bond and right bond instead? think about it
    setPosition(new_x, Utils::window_y * Utils::catchline_y);
  else if (new_x < length / 2)
    setPosition(length / 2, Utils::window_y * Utils::catchline_y);
  else
    setPosition(Utils::window_x - length / 2, Utils::window_y * Utils::catchline_y);

  old_time = std::clock();

}

void Racquet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::vector<sf::Vertex> vertices;

  vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x - length / 2, getPosition().y - height / 2)));
  vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x - length / 2, getPosition().y + height / 2)));
  vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x + length / 2, getPosition().y - height / 2)));  
  vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x + length / 2, getPosition().y + height / 2)));


  target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip);
}

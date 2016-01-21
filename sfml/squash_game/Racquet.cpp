#include <SFML/Graphics.hpp>
#include "Racquet.h"
#include "Thing.h"
#include "Utils.h"
#include <math.h>


void Racquet::changePosition(int xx, int yy)
{
  angle = 0;
  speed = 0;
  old_x = xx;
  old_y = yy;
  old_time = std::clock();
  setPosition(xx, yy);
}

void Racquet::updatePosition(int mouse_x)
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
      angle = 1 * Utils::Pi;
  
    std::clock_t now = std::clock();

    if (getPosition().x != old_x && now != old_time)
    {
      if (getPosition().x > old_x)
        speed = 300 * (getPosition().x - old_x) / (std::clock() - old_time);
      else
        speed = 300 * (old_x - getPosition().x) / (std::clock() - old_time);
    }
  }

  old_x = getPosition().x;
  old_y = getPosition().y;
  
  if (not (mouse_x < Utils::left_wall_d + int(length / 2) || mouse_x > int(Utils::right_wall_d - length / 2)))
    setPosition(mouse_x, Utils::catchline_y);
  else if (mouse_x < Utils::left_wall_d + int(length / 2))
    setPosition(Utils::left_wall_d + int(length / 2), Utils::catchline_y);
  else
    setPosition(Utils::right_wall_d - length / 2, Utils::catchline_y);

  old_time = std::clock();

}

std::vector<std::vector<int>> Racquet::getBorders() const
{
  std::vector<std::vector<int>> borders {{int(getPosition().x - length / 2), int(getPosition().y - height / 2)}, 
                                         {int(getPosition().x + length / 2), int(getPosition().y + height / 2)}};

  return borders;
}

void Racquet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

  std::vector<sf::Vertex> vertices;
  std::vector<std::vector<int>> sign {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  for (unsigned i = 0; i < sign.size(); i++)
    vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x + sign[i][0] * length / 2, getPosition().y + sign[i][1] * height / 2)));

  target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip);
}

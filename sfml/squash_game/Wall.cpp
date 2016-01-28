#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Thing.h"

std::vector<std::vector<int>> Wall::getBorders() const
{
  std::vector<std::vector<int>> borders {{int(getPosition().x - length / 2), int(getPosition().y - height / 2)}, 
                                         {int(getPosition().x + length / 2), int(getPosition().y + height / 2)}};

  return borders;
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
  std::vector<sf::Vertex> vertices;
  const int sign [][2] {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  for (int i = 0; i < 4; i++)
    vertices.push_back(sf::Vertex(sf::Vector2f(getPosition().x + sign[i][0] * length / 2, getPosition().y + sign[i][1] * height / 2)));

  target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip);
}

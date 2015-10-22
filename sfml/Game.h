#include <SFML/Graphics.hpp>

class Game
{
  sf::RectangleShape line_top;
  sf::RectangleShape line_left;
  sf::RectangleShape line_right;
  sf::RectangleShape racquet;//replace all Shapes with things, shapes should be inside.
  sf::CircleShape ball;

public:
  Game();
  void show(sf::RenderWindow& window);
};


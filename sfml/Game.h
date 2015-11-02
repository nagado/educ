#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"


class Game
{
  sf::RectangleShape line_top;
  sf::RectangleShape line_left;
  sf::RectangleShape line_right;
  sf::RectangleShape racquet;//replace all Shapes with things, shapes should be inside.
  Ball ball;

public:
  Game(sf::RenderWindow& window);

  void update();
  bool isOver();
  void show(sf::RenderWindow& window);
  void showGameOver(sf::RenderWindow& window);
};

#endif

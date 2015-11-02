#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Racquet.h"


class Game
{
  sf::RectangleShape line_top;
  sf::RectangleShape line_left;
  sf::RectangleShape line_right;
  Racquet racquet;//replace all Shapes with things, shapes should be inside.
  Ball ball;

public:
  Game(sf::RenderWindow& window);

  //wait for the player
  //void setScene(sf::RenderWindow& window)
  void update(const sf::RenderWindow& window);
  bool isOver();
  void show(sf::RenderWindow& window);
  void showGameOver(sf::RenderWindow& window);//make that real
};

#endif

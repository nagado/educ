#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Racquet.h"
#include "Wall.h"
#include <memory>


class Game
{
  std::vector<std::unique_ptr<Thing>> objects;

public:
  Game(sf::RenderWindow& window);
  ~Game() {}

  void update(const sf::RenderWindow& window);
  bool areColliding(std::vector<std::vector<int>> thing1_borders, std::vector<std::vector<int>> thing2_borders);
  void show(sf::RenderWindow& window);

  bool isOver();
  void showGameOver(sf::RenderWindow& window);

};

#endif

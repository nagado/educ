#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Racquet.h"
#include "Wall.h"
#include <memory>


class Game
{
  Ball ball;
  Racquet racquet;
  std::vector<std::unique_ptr<Wall>> walls;

public:
  Game(sf::RenderWindow& window);
  ~Game() {}

  void update(const sf::RenderWindow& window);
  void show(sf::RenderWindow& window);

  bool areColliding(std::vector<std::vector<int>> thing1_borders, std::vector<std::vector<int>> thing2_borders);
  void handleBallCollision(const std::vector<std::vector<int>> thing_borders, const int thing_speed, const double thing_angle);
  double balanceAngle(double a);

  bool isOver();
  void showGameOver(sf::RenderWindow& window);

};

#endif

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.h"
#include "Utils.h"
#include "Ball.h"
#include "Racquet.h"

Game::Game(sf::RenderWindow& window) 
{
  using namespace Utils;

  line_top.setSize(sf::Vector2f(window_x, line_w));
  line_top.setPosition(0, line_w);

  line_left.setSize(sf::Vector2f(window_y, line_w));
  line_left.setPosition(line_w * 2, 0);
  line_left.rotate(90.f);


  line_right.setSize(sf::Vector2f(window_y, line_w));
  line_right.setPosition(window_x - line_w, 0);
  line_right.rotate(90.f);

  sf::Mouse::setPosition(sf::Vector2i(int(window_x / 2), int(window_y * catchline_y)), window);

  racquet.setDimentions(racquet_x * window_x, racquet_y * window_y);
  racquet.changePosition(window_x / 2 - window_x * racquet_x / 2, catchline_y * window_y);

  ball.setRadius(ball_r * window_y);
  ball.changePosition(int(window_x / 2 - window_y * ball_r), int(window_y * ball_start_height));
  ball.setAngle(1.5);
  ball.setSpeed(1);
  
}

void Game::update(const sf::RenderWindow& window)
{
  ball.updatePosition();
  racquet.updatePosition(window);
}

void Game::show(sf::RenderWindow& window)
{
  window.clear();
  window.draw(line_top);
  window.draw(line_left);
  window.draw(line_right);
  window.draw(racquet);
  window.draw(ball);
  window.display();
} 

bool Game::isOver()
{
  if (ball.getPosition().y > Utils::window_y)
    return true;
  else
    return false;
}

void Game::showGameOver(sf::RenderWindow& window)
{
  window.clear();
}

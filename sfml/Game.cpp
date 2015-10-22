#include "Game.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>

Game::Game() 
{
  using namespace Utils;

  line_top.setSize(sf::Vector2f(window_x, line_w * window_x));
  line_left.setSize(sf::Vector2f(window_y, line_w * window_x));
  line_right.setSize(sf::Vector2f(window_y, line_w * window_x));
  racquet.setSize(sf::Vector2f(racquet_x * window_x, racquet_y * window_y));
  ball.setRadius(ball_r * window_y);

  line_top.setPosition(0, line_w * window_x);
  line_left.setPosition(line_w * window_x * 2, 0);
  line_right.setPosition(window_x - line_w * window_x, 0);
  racquet.setPosition(window_x / 2, catchline_y * window_y);
  ball.setPosition(window_x / 2, window_y * 0.2);

  line_left.rotate(90.f);
  line_right.rotate(90.f);
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



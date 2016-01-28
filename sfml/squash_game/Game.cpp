#include <SFML/Graphics.hpp>
#include <math.h>
#include "Game.h"
#include "Utils.h"
#include "Ball.h"
#include "Racquet.h"
#include <type_traits>
#include <memory>


Game::Game(sf::RenderWindow& window) : ball(Ball(int(Utils::window_x / 2 - Utils::ball_r), Utils::ball_start_height, Utils::ball_r, Utils::ball_angle, Utils::ball_speed)),
                                       racquet(Racquet(int(Utils::window_x / 2 - Utils::racquet_x / 2), Utils::catchline_y, Utils::racquet_x, Utils::racquet_y))
{
  using namespace Utils;

  walls.push_back(std::unique_ptr<Wall> (new Wall(int(window_x / 2), top_wall_d + int(line_w / 2), window_x, line_w)));
  walls.push_back(std::unique_ptr<Wall> (new Wall(left_wall_d + int(line_w / 2), int(window_y / 2), line_w, window_x)));
  walls.push_back(std::unique_ptr<Wall> (new Wall(right_wall_d - int(line_w / 2), int(window_y / 2), line_w, window_x)));
  
  sf::Mouse::setPosition(sf::Vector2i(int(window_x / 2), catchline_y), window);
}

void Game::update(const sf::RenderWindow& window)
{
  for (unsigned i = 0; i < walls.size(); ++i)
    if ( areColliding(ball.getBorders(), walls[i]->getBorders()) )
      handleBallCollision(walls[i]->getBorders(), walls[i]->getSpeed(), walls[i]->getAngle());


  if ( areColliding(ball.getBorders(), racquet.getBorders()) )
    handleBallCollision(racquet.getBorders(), racquet.getSpeed(), racquet.getAngle());
 
  ball.updatePosition();
  racquet.updatePosition(sf::Mouse::getPosition(window).x);
}

void Game::show(sf::RenderWindow& window)
{
  window.clear();
  
  window.draw(ball);
  window.draw(racquet);

  for (unsigned i = 0; i < walls.size(); ++i)
    window.draw(*walls[i].get());

  window.display();
} 

bool Game::areColliding(std::vector<std::vector<int>> thing1_borders, std::vector<std::vector<int>> thing2_borders)
{
  int start1 [] {thing1_borders[0][0], thing1_borders[0][1]};
  int endOf1 [] {thing1_borders[1][0], thing1_borders[1][1]};
  int start2 [] {thing2_borders[0][0], thing2_borders[0][1]};
  int endOf2 [] {thing2_borders[1][0], thing2_borders[1][1]};

  bool colliding [] {false, false};

  if ((start1[0] <= start2[0] and endOf1[0] >= start2[0]) or
      (start1[0] <= endOf2[0] and endOf1[0] >= endOf2[0]) or
      (start1[0] >= start2[0] and endOf1[0] <= endOf2[0]))
    colliding[0] = true;

  if ((start1[1] <= start2[1] and endOf1[1] >= start2[1]) or
      (start1[1] <= endOf2[1] and endOf1[1] >= endOf2[1]) or
      (start1[1] >= start2[1] and endOf1[1] <= endOf2[1]))
    colliding[1] = true;

  return colliding[0] && colliding[1];
}

double Game::balanceAngle(double a)
{
  a = a - 2 * Utils::Pi * int(a / (2 * Utils::Pi));

  if (a < 0)
    a += 2 * Utils::Pi;

  return a;
}

void Game::handleBallCollision(const std::vector<std::vector<int>> thing_borders, const int thing_speed, const double thing_angle)
{
  int start1 [] {thing_borders[0][0], thing_borders[0][1]};
  int endOf1 [] {thing_borders[1][0], thing_borders[1][1]};

  double angle = ball.getAngle();
  int speed = ball.getSpeed();
  
    
  if (ball.getPosition().y <= start1[1])
  {
    angle = 2 * Utils::Pi - angle;
    
    if (angle != thing_angle && thing_speed != 0)
    {
      double side = 0;
      
      if (thing_angle == 0)
      {
        side = sqrt(speed * speed + thing_speed * thing_speed - 2 * speed * thing_speed * cos(Utils::Pi - angle));
        angle = acos((side * side + thing_speed * thing_speed - speed * speed) / (2 * side * thing_speed));
      }
      else
      {
        side = sqrt(speed * speed + thing_speed * thing_speed - 2 * speed * thing_speed * cos(angle));
        angle = Utils::Pi - acos((side * side + thing_speed * thing_speed - speed * speed) / (2 * side * thing_speed));
      }

      if (angle == 0)
        angle = 0.1 * Utils::Pi;

      if (angle == Utils::Pi)
        angle = 0.9 * Utils::Pi;
    }
  }

  else if (ball.getPosition().y >= endOf1[1] and angle <= Utils::Pi)
      angle = 2 * Utils::Pi - angle; 

  else
    angle = balanceAngle(1 * Utils::Pi - angle);


   if (angle == 0)
     angle = 1.1 * Utils::Pi;

   if (angle == Utils::Pi)
     angle = 1.9 * Utils::Pi;

   ball.setAngle(angle);
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

  sf::Font font;
  if (font.loadFromFile("ubuntu-font-family-0.83/Ubuntu-R.tff"))
  {
    sf::Text text;
    text.setFont(font);
    text.setString("GAME OVER");
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);
  }
}

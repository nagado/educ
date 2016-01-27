#include <SFML/Graphics.hpp>
#include "TextException.h"
#include <math.h>
#include "Game.h"
#include "Utils.h"
#include "Ball.h"
#include "Racquet.h"
#include <memory>


Game::Game(sf::RenderWindow& window) 
{
  using namespace Utils;

  objects.push_back(std::unique_ptr<Ball> (new Ball(int(window_x / 2 - ball_r), ball_start_height, ball_r, ball_angle, ball_speed)));
  objects.push_back(std::unique_ptr<Racquet> (new Racquet(int(window_x / 2 - racquet_x / 2), catchline_y, racquet_x, racquet_y)));
  objects.push_back(std::unique_ptr<Wall> (new Wall(int(window_x / 2), top_wall_d + int(line_w / 2), window_x, line_w)));
  objects.push_back(std::unique_ptr<Wall> (new Wall(left_wall_d + int(line_w / 2), int(window_y / 2), line_w, window_x)));
  objects.push_back(std::unique_ptr<Wall> (new Wall(right_wall_d - int(line_w / 2), int(window_y / 2), line_w, window_x)));
  
  sf::Mouse::setPosition(sf::Vector2i(int(window_x / 2), catchline_y), window);
}

void Game::update(const sf::RenderWindow& window)
{
  for (unsigned i = 0; i < objects.size(); ++i)
  {
    if (objects[i]->isMovable())
    {
      bool updated = false;

      for (unsigned k = i + 1; k < objects.size(); ++k)
        if (areColliding(objects[i]->getBorders(), objects[k]->getBorders()))
        {
          objects[i]->updatePosition(objects[k]->getBorders(), objects[k]->getSpeed(), objects[k]->getAngle());
          updated = true;
        }
      
      if (updated == false)  
        objects[i]->updatePosition();
    }

    else
    {
      for (unsigned k = i + 1; k < objects.size(); ++k)
        if (objects[k]->isMovable() and areColliding(objects[k]->getBorders(), objects[i]->getBorders()))
          objects[k]->updatePosition(objects[i]->getBorders(), objects[i]->getSpeed(), objects[i]->getAngle());

      if (objects[i]->needsUpdating())
        objects[i]->updatePosition(sf::Mouse::getPosition(window).x);
    }
  }
}

void Game::show(sf::RenderWindow& window)
{
  window.clear();
  
  for (unsigned i = 0; i < objects.size(); ++i)
    window.draw(*objects[i].get());

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


bool Game::isOver()
{
  bool ball_flying = false;

  for (unsigned i = 0; i < objects.size(); ++i)
    if (objects[i]->isMovable() and objects[i]->getPosition().y > Utils::window_y)
    {
      ball_flying = true;
      break;  
    }

  return ball_flying;
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

#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Game.h"
#include <iostream>//


int main()
{
  sf::RenderWindow window(sf::VideoMode(Utils::window_x, Utils::window_y), "Squash Game", sf::Style::Titlebar|sf::Style::Close);

  Game game(window);

  while (window.isOpen())
  {
    if (game.isOver())
    {
        game.showGameOver(window);
        window.close();
    }
    else
    {
      game.update(window);
      game.show(window);
    }
  }
}

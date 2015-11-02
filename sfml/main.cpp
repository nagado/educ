#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Game.h"
#include <iostream>//


int main()
{
  sf::RenderWindow window(sf::VideoMode(Utils::window_x, Utils::window_y), "Squash Game", sf::Style::Titlebar|sf::Style::Close);
  Game game;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    game.update();
    game.show(window);

  }

  return 0;
}

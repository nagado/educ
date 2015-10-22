#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Game.h"


int main()
{
  sf::RenderWindow window(sf::VideoMode(Utils::window_x, Utils::window_y), "Squash Game", sf::Style::Titlebar|sf::Style::Close);

  while (window.isOpen())
  {
    sf::Event event;
    Game game;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    game.show(window);
  }

  return 0;
}

#include <SFML/Graphics.hpp>
#include "Utils.h"
#include "Game.h"
#include <iostream>//


int main()
{
  sf::RenderWindow window(sf::VideoMode(Utils::window_x, Utils::window_y), "Squash Game", sf::Style::Titlebar|sf::Style::Close);

  Game game(window); //make a start screen with a restarts button outside of a game.

  while (window.isOpen())
  {
    if (game.isOver())
    {
        game.showGameOver(window);
        for (int i = 0; i < 1000000; ++i); // make normal sleep func
        window.close();
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      window.close();
    else
    {
      game.update(window);
      game.show(window);
    }

    sf::Event event;
    
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }
}

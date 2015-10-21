#include <SFML/Graphics.hpp>


int window_x = 600;
int window_y = 400;
int line_width = 3;
int main()
{
  sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Squash Game", sf::Style::Titlebar|sf::Style::Close);
  sf::RectangleShape line_top(sf::Vector2f(window_x, line_width));
  sf::RectangleShape line_left(sf::Vector2f(window_y, line_width));
  sf::RectangleShape line_right(sf::Vector2f(window_y, line_width));

  line_top.setPosition(0, line_width);
  line_left.rotate(90.f);
  line_left.setPosition(line_width * 2, 0);
  line_right.rotate(90.f);
  line_right.setPosition(window_x - line_width, 0);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(line_top);
    window.draw(line_left);
    window.draw(line_right);
    window.display();
  }

  return 0;
}

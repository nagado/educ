#include <SFML/Graphics.hpp>
#include "TextException.h"
#include "Thing.h"
#include <time.h>

void Thing::changePosition(int xx, int yy)
{
  setPosition(xx, yy);
  x = xx;
  y = yy;
}

void Thing::checkPosition()
{
  sf::Vector2f position = getPosition();

  if (position.x - x > 1 || position.x - x < -1 || position.y - y > 1 || position.y - y < -1)
    throw TextException("setPosition function was used. Check the code");
}

//virtual void Thing::update()
//{
//}

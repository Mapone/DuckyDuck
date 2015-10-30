#ifndef STATEESCMENU_H
#define STATEESCMENU_H


#include <SFML/Graphics.hpp>
#include "State.hpp"
class Jeu;

class StateEscMenu : public State
{
public:
  StateEscMenu(Jeu *jeu);
  ~StateEscMenu();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void pressUp();
  virtual void pressDown();
  virtual void pressSpace();
  virtual void pressEsc();

private:
  sf::Text _gameName;
  sf::Text _Reprendre;
  sf::Text _Quitter;
  sf::CircleShape _triangle;
  unsigned int _current;
};

#endif  
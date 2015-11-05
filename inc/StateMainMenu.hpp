#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H


#include <SFML/Graphics.hpp>
#include "State.hpp"
class Jeu;

class StateMainMenu : public State
{
public:
  StateMainMenu(Jeu *jeu);
  ~StateMainMenu();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void pressUp();
  virtual void pressDown();
  virtual void pressEnter();

private:
	sf::Text _gameName;
	sf::Text _Jouer;
	sf::Text _Quitter;
	sf::CircleShape _triangle;
  unsigned int _current;
};

#endif
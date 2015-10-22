#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

class StateMainMenu : public State
{
public:
  StateMainMenu(Jeu *jeu);
  ~StateMainMenu();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void pressUP();
  virtual void pressDown();
  virtual void pressSpace();

private:
	sf::Text _gameName;
	sf::Text _Jouer;
	sf::Text _Quitter;
	sf::CircleShape _triangle;
};

#endif
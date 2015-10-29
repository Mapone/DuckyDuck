#ifndef STATEMENU_H
#define STATEMENU_H

class Bouton;

class StateMenu : public sf::Drawable, public sf::Transformable, public State
{
public:
  StateMenu(Jeu *jeu, Bouton &b;);
  ~StateMenu();
  virtual void pressUp();
  virtual void pressDown();
  virtual void pressLeft();
  virtual void pressRight();
  virtual void pressSpace();
  void addChoice(const Bouton &b);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

private:
	std::Vector _listofChoices<Bouton>;
	unsigned int _selected;

#endif
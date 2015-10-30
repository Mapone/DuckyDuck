#ifndef STATE_H
#define STATE_H

#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"

class State : public sf::Drawable, public sf::Transformable
{
public:
  State(Jeu *jeu);
  ~State();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void init();
  virtual void pressSpace() = 0;
  virtual void pressUp() = 0;
  virtual void pressDown() = 0;
  virtual void pressEsc();
  virtual void pressLeft();
  virtual void pressRight();

protected:
	Jeu *_jeu;
};

#endif
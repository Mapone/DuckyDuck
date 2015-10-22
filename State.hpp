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
  virtual void pressUP() = 0;
  virtual void pressDown() = 0;
  virtual void pressLeff();
  virtual void pressRight();
  virtual void pressSpace() = 0;

protected:
	Jeu *_jeu;
};

#endif
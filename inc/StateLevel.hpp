#ifndef STATELEVEL_H
#define STATELEVEL_H

#include <SFML/Graphics.hpp>
#include "State.hpp"
class TileMap;
class Jeu;
class Personnage;

class StateLevel : public State
{
public:
  StateLevel(Jeu* jeu, TileMap& tilemap, Personnage& perso);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void init();
  virtual void update() const;
  virtual void pressUp();
  virtual void pressDown();
  virtual void pressLeft();
  virtual void pressRight();
  virtual void pressSpace();
  virtual void updateCamera() const;


private:
  TileMap& _tilemap;
  Personnage& _perso;
  void checkMapCollision() const;

};

#endif
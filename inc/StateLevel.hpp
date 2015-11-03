#ifndef STATELEVEL_H
#define STATELEVEL_H

/**
* \file State.hpp
* \brief State
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 3/11/2015
*
* Interface du Pattern State
*/

#include <SFML/Graphics.hpp>
#include "State.hpp"
class TileMap;
class Jeu;
class Personnage;

/**
* \classe StateLevel
* \brief Etat StateLevel rattaché au Pattern State
*/
class StateLevel : public State
{
public:

  /**
  * \brief Constructeur
  *
  * Constructeur de la classe State
  * 
  * \param jeu : Jeu sur lequel le Pattern State s'applique, perso : Personnage jouable
  */
  StateLevel(Jeu* jeu, TileMap& tilemap, Personnage& perso);

  /**
  * \fn virtual void draw(sf::RenderTarget& target, st::RenderStates states) const
  * \brief Dessine un objet
  * 
  * Prends un objet target et le dessine.
  *
  * \param target : objet à dessiner, states : applique la transformation (SFML Function)
  */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  /**
  * \fn virtual void init()
  * \brief initialise les coord. du spawn du personnage
  *
  * Initialise pour les niveaux les coordonnées du Personnage jouable.
  */
  virtual void init();

  /**
  * \fn virtual void pressSpace() = 0;
  * \brief Action à effectuer quand Espace est appuyé
  *
  * Gère les actions rattachées à la barre d'espace.
  */
  virtual void pressSpace();

  /**
  * \fn virtual void pressUp() = 0;
  * \brief Action à effectuer quand la touche Haut est appuyé
  *
  * Gère les actions rattachées à la touche Haut.
  */
  virtual void pressUp();

  /**
  * \fn virtual void pressDown() = 0;
  * \brief Action à effectuer quand la touche Bas est appuyé
  *
  * Gère les actions rattachées à la touche Bas.
  */
  virtual void pressDown();

  /**
  * \fn virtual void pressEsc() = 0;
  * \brief Action à effectuer quand la touche Echap est appuyé
  *
  * Gère les actions rattachées à la touche Echap.
  */
  virtual void pressEsc();

  /**
  * \fn virtual void pressLeft() = 0;
  * \brief Action à effectuer quand la touche Gauche est appuyé
  *
  * Gère les actions rattachées à la touche Gauche.
  */
  virtual void pressLeft();

  /**
  * \fn virtual void pressRight() = 0;
  * \brief Action à effectuer quand la touche Droite est appuyé
  *
  * Gère les actions rattachées à la touche Droite.
  */
  virtual void pressRight();


private:

  TileMap& _tilemap; /** TileMap du niveau */
  Personnage& _perso; /** Personnage jouable */

  /**
  * \fn void update() const;
  * \brief Vérifie les collisions de la map
  *  et update la caméra.
  */
  void update() const;

  /**
  * \fn void checkMapCollision() const
  * \brief Vérifie les collisions et agit en conséquence
  *
  * Vérifie si le Personnage jouable est en collision avec le niveau
  * et agit en conséquence.
  */
  void checkMapCollision() const;

  /**
  * \fn void updateCamera() const
  * \brief update la caméra
  */
  void updateCamera() const;

};

#endif
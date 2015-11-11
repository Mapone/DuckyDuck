#ifndef STATE_H
#define STATE_H

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

#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"

/**
* \classe State
* \brief Interface du State
*/
class State : public sf::Drawable, public sf::Transformable
{
public:

  /**
  * \brief Constructeur
  *
  * Constructeur de la classe State
  * 
  * \param jeu : Jeu sur lequel le Pattern State s'applique
  */
  State(Jeu *jeu);

  /**
  * \brief Destructeur
  *
  * Destructeur de la classe State
  */
  ~State();

  /**
  * \fn virtual void draw(sf::RenderTarget& target, st::RenderStates states) const
  * \brief Dessine un objet
  * 
  * Prends un objet target et le dessine.
  *
  * \param target : objet à dessiner, states : applique la transformation (SFML Function)
  */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

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
  virtual void pressUp() = 0;

  /**
  * \fn virtual void pressDown() = 0;
  * \brief Action à effectuer quand la touche Bas est appuyé
  *
  * Gère les actions rattachées à la touche Bas.
  */
  virtual void pressDown() = 0;

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

  /**
  * \fn virtual void pressEnter;
  * \brief Action à effectuer quand la touche Entrée est appuyé
  *
  * Gère les actions rattachées à la touche Entrée.
  */
  virtual void pressEnter();

  virtual void update();


protected:
	Jeu *_jeu; /** Jeu rattaché au Pattern */
};

#endif
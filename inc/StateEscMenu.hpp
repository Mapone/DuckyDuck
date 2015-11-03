#ifndef STATEESCMENU_H
#define STATEESCMENU_H

/**
* \file StateEscMenu.hpp
* \brief State
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 3/11/2015
*
* Etat EscMenu rattaché au Pattern State.
*/

#include <SFML/Graphics.hpp>
#include "State.hpp"
class Jeu;

/**
* \classe State
* \brief Etat EscMenu rattaché au Pattern State
*/
class StateEscMenu : public State
{
public:

  /**
  * \brief Constructeur
  *
  * Constructeur de la classe State
  * 
  * \param jeu : Jeu sur lequel le Pattern State s'applique
  */
  StateEscMenu(Jeu *jeu);

  /**
  * \brief Destructeur
  *
  * Destructeur de la classe State
  */
  ~StateEscMenu();

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

  /**
  * \fn virtual void pressSpace() = 0;
  * \brief Action à effectuer quand Espace est appuyé
  *
  * Gère les actions rattachées à la barre d'espace.
  */
  virtual void pressSpace();

  /**
  * \fn virtual void pressEsc() = 0;
  * \brief Action à effectuer quand la touche Echap est appuyé
  *
  * Gère les actions rattachées à la touche Echap.
  */
  virtual void pressEsc();

private:
  sf::Text _gameName; /** Nom du jeu */
  sf::Text _Reprendre; /** Affichage pour reprendre */
  sf::Text _Quitter; /** Affichage pour quitter */
  sf::CircleShape _triangle; /** Curseur pour le choix */
  unsigned int _current; /** Choix en cours */
};

#endif  
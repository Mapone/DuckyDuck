#ifndef STATEESCMENU_H
#define STATEESCMENU_H

/**
* \file StateEscMenu.hpp
* \brief Menu Pause du jeu
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 3/11/2015
*
* Etat StateEscMenu rattaché au Pattern State.
*/

#include <SFML/Graphics.hpp>
#include "State.hpp"
class Jeu;

/**
* \classe StateEscMenu
* \brief Etat StateEscMenu rattaché au Pattern State
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
      * \fn virtual void pressEnter() = 0;
      * \brief Action à effectuer quand Entrée est appuyé
      *
      * Gère les actions rattachées à la touhce Entrée.
      */
      virtual void pressEnter();

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
      sf::Text _Recommencer; /** Affichage pour recommencer le niveau */
      sf::Text _Quitter; /** Affichage pour quitter */
      sf::CircleShape _triangle; /** Curseur pour le choix */
      unsigned int _current; /** Choix en cours */
};

#endif  
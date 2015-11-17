#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H


#include <SFML/Graphics.hpp>
#include "State.hpp"


/**
* \file StateMainMenu.hpp
* \brief Menu principal
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 3/11/2015
*
* Etat MainMenu rattaché au Pattern State.
*/


class Jeu;


/**
* \classe StateMainMenu
* \brief Etat MainMenu rattaché au Pattern State.
*/
class StateMainMenu : public State
{
    public:

        /**
        * \brief Constructeur
        *
        * Constructeur de la classe StateMainMenu
        *
        * \param jeu : jeu sur lequel s'applique le menu
        */
        StateMainMenu(Jeu *jeu);

        /**
        * \brief Destructeur
        *
        * Destructeur de la classe StateMainMenu
        */
        ~StateMainMenu();

        /**
        * \fn virtual void draw(sf::RenderTarget& target, st::RenderStates states) const
        * \brief Dessine le menu
        * 
        * Dessine le menu principal
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

    private:
      sf::Text _gameName; /** Nom du jeu */
      sf::Text _Jouer; /** Texte afficher pour jouer */
      sf::Text _Quitter; /** Texte afficher pour quitter */
      sf::CircleShape _triangle; /** Curseur */
      unsigned int _current; /** Choix courant */
};

#endif
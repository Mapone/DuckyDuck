#ifndef STATESTATS_H
#define STATESTATS_H


#include <SFML/Graphics.hpp>
#include "State.hpp"


/**
* \file StateStats.hpp
* \brief Affichage en fin de niveau
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Etat StateStats rattaché au Pattern State.
*/


class Personnage;


/**
* \classe StateStats
* \brief Etat StateStats rattaché au Pattern State.
*/
class StateStats : public State
{
    public:
        /**
        * \brief Constructeur
        * 
        * Constructeur de la classe StateStats
        *
        * \param jeu : jeu sur lequel on applique les stats, p : personnage sur lequel les stats sont enregistrés
        */
        StateStats(Jeu *jeu, Personnage& p);

        /**
        * \brief Destrcuteur
        *
        * Destructeur de la classe StateStats
        */
        ~StateStats();

        /**
        * \fn virtual void draw(sf::RenderTarget& target, st::RenderStates states) const
        * \brief Dessine le menu
        * 
        * Dessine le menu des stats
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
        * \fn void setIsLevelFinished(bool IsLevelFinished)
        * \brief Setter du bool IsLevelFinished
        *
        * Setter pour le bool de fin de partie
        *
        * \param IsLevelFinished : valeur qui remplacera l'ancienne
        */
        void setIsLevelFinished(bool IsLevelFinished);

    private:

        /**
        * \fn void init()
        * \brief Gère l'affichage en fonction de la réussite (ou non du niveau)
        *
        * Affiche la réussite ou non du niveau
        */
        void init();
        sf::Text _levelName; /** Nom du niveau */
        sf::Text _scoreTxt; /** Texte du Score */
        sf::Text _scoreNb; /** Nombre de points */
        sf::Text _enemyTxt; /** Texte des ennemis tués */
        sf::Text _enemyNb; /** Nombre d'ennemis tués */
        sf::Text _timeTxt; /** Texte du temps écoulé */
        sf::Text _timeNb; /** Temps écoulé */
        sf::Text _pressSpace; /** Texte pour l'effet de la barre d'espace */
        bool _isLevelFinished; /** Jeu Niveau fini? */
        Personnage& _perso; /** Personnage sur le niveau */
};

#endif
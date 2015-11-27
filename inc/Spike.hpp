#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.hpp"

/**
* \file Spike.hpp
* \brief Classe des ennemis immobiles
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 27/11/2015
*
* Définit un Enemy ne pouvant que pas bouger et tuantà chaque collision
* Hérite de Enemy.
*/

class TileMap;
class Personnage;

/**
* \class Spike
* \brief Classe gérant les pics
*/
class Spike : public Enemy
{
	public:

		/**
		* \brief Constructeur
		*
		* Constructeur de la classe Spike
		*
		* \param taille : Taille de la pic, tilemap : map sur laquelle l'ennemi existe
		*/
		Spike(const sf::Vector2f taille, TileMap& tilemap);

		/**
		* \fn Enemy* clone()
		* \brief Clone l'Enemy
		*
		* \return Un clone de l'ennemi
		*/
		Enemy* clone();

		/**
		* \fn bool jumpOn()
		* \brief Action lorsque que l'on saute sur un Boomer
		*
		* \return Return true si le personnage dois mourir
		*/
		bool jumpOn();

		/**
		* \fn void move()
		* \brief Fonction bougeant l'ennemi.
		*
		* Fonction utilisant le Pattern Strategy AI pour mouvoir l'ennemi
		* Attention, ici pas d'AI, donc initialisation du mouvement à immobile
		* (une pic qui bouge, c'est pas normal en même temps!)
		*/
		virtual void move();
};

#endif
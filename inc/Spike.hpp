#ifndef SPIKE_H
#define SPIKE_H

#include "Enemy.hpp"

/**
* \file Spike.hpp
* \brief Classe des ennemis immobiles
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit un Enemy ne pouvant que pas bouger et tuantà chaque collision
* Hérite de Enemy.
*/

class TileMap;
class Personnage;

/**
* \class Follower
* \brief Classe gérant les pics
*/
class Spike : public Enemy
{
	public:
		Spike(const sf::Vector2f taille, TileMap& tilemap);
		Enemy* clone();
		bool jumpOn();
		void move();
};

#endif
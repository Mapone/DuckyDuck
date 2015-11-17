#ifndef WALKER_H
#define WALKER_H

#include "Enemy.hpp"

/**
* \file Walker.hpp
* \brief Classe des ennemis marchant
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit un Enemy ne pouvant que marcher
* Hérite de Enemy.
*/

class TileMap;

/**
* \class Walker
* \brief Classe gérant les ennemi qui marchent.
*/
class Walker : public Enemy
{
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe Walker
	*
	* \param taille : taille de l'Enemy, tilemap : map sur lequel le Walker sera.
	*/
	Walker(const sf::Vector2f &taille, const TileMap& tilemap);

	/**
	* \fn Enemy* clone();
	* \brief Clone le Walker
	*
	* Créer un nouveau Walker avec les même caractéristiques.
	*
	* \return Un clone du Walker existant
	*/
	Enemy* clone();
};


#endif
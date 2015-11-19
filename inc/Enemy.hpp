#ifndef ENEMY_H
#define ENEMY_H

#include "AliveEntity.hpp"


/**
* \file Enemy.hpp
* \brief Classe définissant les ennemis
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit les ennemis du Personnage.
* Hérite de AliveEntity.
*/

class AI;
class TileMap;


/**
* \class Enemy
* \brief Classe abstraite qui définissant les objets "vivants"
*
* Classe définissant un ennemi.
*/
class Enemy : public AliveEntity
{
public:

	/**
	* \brief Constructeur
	* 
	* Constructeur de la classe Enemy
	*
	* \param taille : taille de l'objet, tilemap : TileMap à laquelle l'ennemi est rattaché.
	*/
	Enemy(const sf::Vector2f &taille, TileMap &tilemap);

	/**
	* \brief Destrcuteur
	*
	* Destructeur de la classe Enemy
	*/
	virtual ~Enemy();

	/**
	* \fn void move()
	* \brief Fonction bougeant l'ennemi.
	*
	* Fonction utilisant le Pattern Strategy AI pour mouvoir l'ennemi
	* 
	*/
	void move();

	/**
	* \fn virtual Enemy* clone()
	* \brief Permet de clone l'ennemi (Pattern Prototype)
	*
	* Permet de cloner un objet afin d'en instancier
	* un certain nombre facilement.
	* 
	* \return Retourne un nouvel Enemy.
	*/
	virtual Enemy* clone() = 0;

	/**
	 * @brief Actions à faire si on saute sur l'ennemi
	 * @details Actions à faire si on saute sur l'ennemi
	 */
	virtual void jumpOn();

	/**
	* 
	*/
	virtual unsigned int getReward() const;

protected:
	AI* _AI; /** IA de l'ennemi */

	//L'enemi doit avoir conscience de sa TileMap
	TileMap& _tileMap; /** TileMap sur laquelle l'ennemi existe. */

};


#endif
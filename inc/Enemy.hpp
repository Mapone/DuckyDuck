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
* \brief Classe abstraite qui définissant les ennemis
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
	virtual void move();

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
	 * \fn bool jumpOn()
	 * @brief Actions à faire si on saute sur l'ennemi
	 * @details Actions à faire si on saute sur l'ennemi
	 *
	 * \return Retourne vrai si le personnage doit mourir
	 */
	virtual bool jumpOn();

	/**
	* \fn unsigned int getReward() const 
	* \brief Récompense lors de la mort de l'Enemy
	*
	* \return Le nombre de point gagné
	*/
	virtual unsigned int getReward() const;

	/**
	* \fn bool isDead()
	* \brief Getter de _isDead
	*
	* Retourne l'état (Mort ou vif) de l'Enemy
	*
	* \return La valeur de _isDead
	*/
	bool isDead();


protected:
	AI* _AI; /** IA de l'ennemi */

	//L'enemi doit avoir conscience de sa TileMap
	TileMap& _tileMap; /** TileMap sur laquelle l'ennemi existe. */
	bool _isDead; /** Boolean définissant son état */
	sf::Texture _texture; /** Texture de l'Enemy */
};


#endif
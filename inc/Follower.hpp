#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Enemy.hpp"

/**
* \file Follower.hpp
* \brief Classe des ennemis marchant
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit un Enemy ne pouvant que marcher
* Hérite de Enemy.
*/

class TileMap;
class Personnage;

/**
* \class Follower
* \brief Classe gérant les ennemi qui marchent.
*/
class Follower : public Enemy
{
public:

	/**
	 * @brief Constructeur du Follower
	 * @details Constructeur du Follower
	 * 
	 * @param taille Taille de la hitbox
	 * @param tilemap Map sur laquelle est l'ennemi
	 * @param perso Le personnage à suivre
	 * @param speed Sa vitesse, en pixels par frame
	 * @param jumpHeight Sa hauteur de saut, poussée en Y
	 */
	Follower(const sf::Vector2f &taille, TileMap& tilemap, const Personnage& perso, float speed, float jumpHeight);

	/**
	* \fn Enemy* clone();
	* \brief Clone le Follower
	*
	* Créer un nouveau Follower avec les même caractéristiques.
	*
	* \return Un clone du Follower existant
	*/
	Enemy* clone();

	/**
	 * \fn float getSpeed() const
	 * @brief Getter de la vitesse du l'ennemi
	 * @details Getter de la vitesse de l'ennemi, en pixels par frame
	 * @return Le deplacement de l'ennemi à chaque frame
	 */
	float getSpeed() const;

	/**
	 * \fn float getJumpHeight() const
	 * @brief Getter de la hauteur de saut de l'ennemi
	 * @details Getter de la Hauteur de saut de l'ennemi, soit la pourssée en Y lors du saut
	 * @return La valeur de la poussée en Y
	 */
	float getJumpHeight() const;

	/**
	* \fn bool jumpOn()
	* \brief Action lorsque que l'on saute sur un Boomer
	*
	* \return Return true si le personnage dois mourir
	*/
	bool jumpOn();

	/**
	* \fn unsigned int getReward() const 
	* \brief Récompense lors de la mort de l'Enemy
	*
	* \return Le nombre de point gagné
	*/
	virtual unsigned int getReward() const; 
	
private:
	const Personnage& _perso; /** Personnage à suivre */
	float _speed; /** Vitesse de l'ennemi */
	float _jumpHeight; /** Poussé pour le saut */
};


#endif
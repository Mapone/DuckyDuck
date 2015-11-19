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
	 * @param float Sa vitesse, en pixels par frame
	 * @param float Sa hauteur de saut, poussée en Y
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
	 * @brief Getter de la vitesse du l'ennemi
	 * @details Getter de la vitesse de l'ennemi, en pixels par frame
	 * @return Le deplacement de l'ennemi à chaque frame
	 */
	float getSpeed() const;

	/**
	 * @brief Getter de la hauteur de saut de l'ennemi
	 * @details Getter de la Hauteur de saut de l'ennemi, soit la pourssée en Y lors du saut
	 * @return La valeur de la poussée en Y
	 */
	float getJumpHeight() const;

	void jumpOn();

	unsigned int getReward() const; 
	
private:
	const Personnage& _perso;
	float _speed;
	float _jumpHeight;
};


#endif
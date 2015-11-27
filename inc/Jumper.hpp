#ifndef JUMPER_H
#define JUMPER_H

#include "Enemy.hpp"

/**
* \file Jumper.hpp
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
* \class Jumper
* \brief Classe gérant les ennemi qui marchent.
*/
class Jumper : public Enemy
{
public:

	/**
	 * @brief Constructeur du Jumper
	 * @details Constructeur du Jumper
	 * 
	 * @param taille Taille de la hitbox
	 * @param tilemap Map sur laquelle est l'ennemi
	 * @param int Sa vitesse, en pixels par frame
	 * @param int Sa hauteur de saut, poussée en Y
	 */
	Jumper(const sf::Vector2f &taille, TileMap& tilemap, int speed, int jumpHeight);

	/**
	* \brief Constructeur
	* 
	* Constructeur de la classe Jumper
	*
	* \param taille Taille de la HitBox
	* \param position Coordonnées de spawn du Jumper
	* \param tileMap TileMap sur laquelle l'enemi va exister
	* \param speed Vitesse du Jumper
	* \param jumpHeight Hauteur du saut du Jumper
	*/
	Jumper(const sf::Vector2f &taille, const sf::Vector2f &position,  TileMap& tilemap, int speed, int jumpHeight);

	/**
	* \fn Enemy* clone();
	* \brief Clone le Jumper
	*
	* Créer un nouveau Jumper avec les même caractéristiques.
	*
	* \return Un clone du Jumper existant
	*/
	Enemy* clone();

	/**
	 * @brief Getter de la vitesse du l'ennemi
	 * @details Getter de la vitesse de l'ennemi, en pixels par frame
	 * @return Le deplacement de l'ennemi à chaque frame
	 */
	int getSpeed() const;

	/**
	 * @brief Getter de la hauteur de saut de l'ennemi
	 * @details Getter de la Hauteur de saut de l'ennemi, soit la pourssée en Y lors du saut
	 * @return La valeur de la poussée en Y
	 */
	int getJumpHeight() const;

	/**
	* \fn unsigned int getReward() const 
	* \brief Récompense lors de la mort de l'Enemy
	*
	* \return Le nombre de point gagné
	*/
	unsigned int getReward() const; 
	
private:
	int _speed; /** Vitesse du Jumper */
	int _jumpHeight; /** Force de la poussé pour les sauts */
};


#endif
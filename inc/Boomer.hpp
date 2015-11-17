#ifndef BOOMER_H
#define BOOMER_H

#include "Enemy.hpp"

/**
* \file Boomer.hpp
* \brief Classe des ennemis qui grossissent puis explosent
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit un Enemy pouvant exploser et se deviser
* Hérite de Enemy.
*/

class TileMap;

/**
* \class Boomer
* \brief Classe gérant les ennemi qui explosent et se devisent
*/
class Boomer : public Enemy
{
public:

	/**
	 * @brief Constructeur du Boomer
	 * @details Constructeur du Boomer
	 * 
	 * @param taille Taille de la hitbox
	 * @param tilemap Map sur laquelle est l'ennemi
	 * @param grossissement par frame 
	 */
	Boomer(const sf::Vector2f &taille, const TileMap& tilemap, int fatPerFrame);

	/**
	* \fn Enemy* clone();
	* \brief Clone le Boomer
	*
	* Créer un nouveau Boomer avec les même caractéristiques.
	*
	* \return Un clone du Boomer existant
	*/
	Enemy* clone();

	/**
	 * @brief Getter du grossissement par frame
	 * @details Getter de grossissement par frame
	 * @return Retourne la valeure du grossissement par frame
	 */
	unsigned int getFatPerFrame() const;

private:
	unsigned int _fatPerFrame;
};


#endif
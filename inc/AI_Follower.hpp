#ifndef AI_FOLLOWER_H
#define AI_FOLLOWER_H

#include <SFML/Graphics.hpp>
#include "AI.hpp"


/**
* \file AI_Follower.hpp
* \brief AI des enemy sautant
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvement d'un Enemy ayant pour base
* le mouvement de saut sur une TileMap définie.
* Hérite de AI.
*/

class Follower;
class Personnage;

/**
* \class AI_Follower
* \brief Classe gérant l'AI des Follower
*/
class AI_Follower : public AI
{
  
public:

	/**
	 * @brief Constructeur de l'IA follower
	 * @details Constructeur de l'IA follower
	 * 
	 * @param follower Pointeur vers l'ennemi
	 * @param tilemap La tileMap sur laquelle est l'ennemi
	 * @param p Le personnage à suivre
	 */
    AI_Follower(Follower* follower, const TileMap& tilemap, const Personnage& p);

    /**
	* \fn virtual void move()
	* \brief Procédure gérant le mouvement de l'ennemi
	*
	* Procédure qui permet de mouvoir l'ennemi
	* en fonction de l'AI qu'il a adopter
	*/
    virtual void move();

private:

	bool _directionX; /** Bool qui vérifiant si l'on doit inverser le mouvement en X (collision) */
	Follower* _follower; /** l'ennemi à deplacer */
	const Personnage& _perso; /**Le personnage à suivre*/
};

#endif
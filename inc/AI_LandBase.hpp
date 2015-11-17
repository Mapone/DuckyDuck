#ifndef AI_LANDBASE_H
#define AI_LANDBASE_H

#include "AI.hpp"


/**
* \file AI_LandBase.hpp
* \brief AI des enemy au sol
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvement d'un Enemy ayant pour base
* le mouvement D/G au sol sur une TileMap définie.
* Hérite du AI.
*/

class Enemy;

/**
* \class AI_LandBase
* \brief Classe gérant l'AI des ennemi qui marchent.
*/
class AI_LandBase : public AI
{
  
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe AI_JumpRandom.
	*
	* \param enemy : Ennemi utilisant l'IA, tilemap : TileMap sur laquelle l'Enemy est.
	*/
    AI_LandBase(Enemy* enemy, const TileMap& tilemap);

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
};

#endif
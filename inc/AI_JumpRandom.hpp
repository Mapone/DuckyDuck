#ifndef AI_JUMPRANDOM_H
#define AI_JUMPRANDOM_H

#include <SFML/Graphics.hpp>
#include "AI.hpp"


/**
* \file AI_JumpRandom.hpp
* \brief AI des enemy sautant
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvement d'un Enemy ayant pour base
* le mouvement de saut sur une TileMap définie.
* Hérite du AI.
*/

class Enemy;

/**
* \class AI_JumpRandom
* \brief Classe gérant l'AI des ennemi qui sautent.
*/
class AI_JumpRandom : public AI
{
  
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe AI_JumpRandom.
	*
	* \param enemy : Ennemi utilisant l'IA, tilemap : TileMap sur laquelle l'Enemy est.
	*/
    AI_JumpRandom(Enemy* enemy, const TileMap& tilemap);

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
	sf::Clock _clock; /** ??? */
};

#endif
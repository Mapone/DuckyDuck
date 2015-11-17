#ifndef AI_BOOMER_H
#define AI_BOOMER_H

#include <SFML/Graphics.hpp>
#include "AI.hpp"


/**
* \file AI_Boomer.hpp
* \brief AI des boomers
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvement d'un Enemy ayant pour base
* le mouvement de saut sur une TileMap définie.
* Hérite du AI.
*/

class Boomer;

/**
* \class AI_Boomer
* \brief Classe gérant l'AI des ennemi qui sautent.
*/
class AI_Boomer : public AI
{
  
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe AI_Boomer.
	*
	* \param enemy : Ennemi utilisant l'IA, tilemap : TileMap sur laquelle l'Enemy est.
	*/
    AI_Boomer(Boomer* Boomer, const TileMap& tilemap);

    /**
	* \fn virtual void move()
	* \brief Procédure gérant le mouvement de l'ennemi
	*
	* Procédure qui permet de mouvoir l'ennemi
	* en fonction de l'AI qu'il a adopter
	*/
    virtual void move();

private:
	Boomer* _boomer;
	sf::Clock _clock; /** Clock gérer par SFML */

};

#endif
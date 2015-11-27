#ifndef AI_JUMPER_H
#define AI_JUMPER_H

#include <SFML/Graphics.hpp>
#include "AI.hpp"


/**
* \file AI_Jumper.hpp
* \brief AI des enemy sautant
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvement d'un Enemy qui 
* pourra sauter et/ou se déplacer latéralement.
* Hérite de AI.
*/

class Jumper;

/**
* \class AI_Jumper
* \brief Classe gérant l'AI des Jumper
*/
class AI_Jumper : public AI
{
  
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe AI_Jumper.
	*
	* \param jumper : Ennemi utilisant l'IA, tilemap : TileMap sur laquelle l'Enemy est.
	*/
    AI_Jumper(Jumper* jumper, const TileMap& tilemap);

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
	Jumper* _jumper; /** L'enemy à déplacer */
};

#endif
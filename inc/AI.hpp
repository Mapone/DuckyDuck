#ifndef AI_H
#define AI_H


/**
* \file AI.hpp
* \brief Pattern Stratégy gérant les IA des ennemis
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère les mouvements d'un Enemy sur une map définit.
*/

class Enemy;
class TileMap;

/**
* \class AI
* \brief Classe abstraite pour les IA des ennemis
*/
class AI
{
  
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe AI
	*
	* \param enemy : Ennemi utilisant l'IA, tilemap : tilemap sur laquelle l'enemy est.
	*/
	AI(Enemy* enemy, const TileMap& tilemap);

	/**
	* \brief Destructeur
	*
	* Destructeur de la classe AI
	*/
	virtual ~AI();

	/**
	* \fn virtual void move()
	* \brief Procédure gérant le mouvement de l'ennemi
	*
	* Procédure qui permet de mouvoir l'ennemi
	* en fonction de l'AI qu'il a adopter
	*/
	virtual void move() = 0;

protected:
	Enemy* _enemy; /** Ennemi qui utilise l'AI */
	const TileMap& _tileMap; /** Tilemap sur lequel l'ennemi est. */
};

#endif
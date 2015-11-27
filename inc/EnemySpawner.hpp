#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.hpp"

/**
* \file EnemySpawner.hpp
* \brief Classe des ennemis qui grossissent puis explosent
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit un Enemy pouvant exploser et se deviser
* Hérite de Enemy.
*/

class Spawner;
class TileMap;

/**
* \class EnemySpawner
* \brief Classe gérant les spawners d'Enemy
*/
class EnemySpawner : public Enemy
{
public:

	/**
	 * @brief Constructeur
	 * @details Constructeur du EnemySpawner
	 * 
	 * @param taille Taille de la hitbox
	 * @param tilemap Map sur laquelle est l'ennemi
	 * @param grossissement par frame 
	 * @param l'ennemi qui sortiera une fois le EnemySpawner tué
	 */
	EnemySpawner(TileMap& tilemap, Enemy* enemy, float spawnfreq);

	~EnemySpawner();

	/**
	* \fn Enemy* clone()
	* \brief Clone le EnemySpawner
	*
	* Créer un nouveau EnemySpawner avec les même caractéristiques.
	*
	* \return Un clone du EnemySpawner existant
	*/
	Enemy* clone();

	/**
	* \fn void move()
	* \brief Action de l'ennemi
	*
	* Bouge l'Enemy
	*/
	void move();

private:
	Spawner* _enemySpawn; /** Ennemi à faire spawn */
	TileMap& _tilemap; /** TileMap sur laquelle l'Enemy est */
	float _spawnfreq; /** Fréquence de spawn */
	sf::Clock _clock; /** Clock pour le spawn d'ennemi */
};


#endif
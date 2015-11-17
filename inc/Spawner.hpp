/**
* \file Spawner.hpp
* \brief Créer une instance de Enemy
* \author {N. Guittonneau,P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Gère le spawn du prototype (ennemi à cloner.)
* Pattern Prototype.
*/


class Enemy;

/**
* \class Personnage
* \brief Classe définissant un personnage.
*/
class Spawner
{
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe Spawner
	*
	* \param prototype : Enemy à cloner
	*/
    Spawner(Enemy* prototype);

    /**
    * \fn Enemy* spawnEnemy()
    * \brief Clone l'Enemy contenu dans le spawner
    *
    * Appelle la fonction clone du prototype
   	*
   	* \return Un nouvel Enemy
    */
    Enemy* spawnEnemy();

private:
    Enemy* prototype_; /** Enemy alpha servant de "modèle" pour le clonage */
};
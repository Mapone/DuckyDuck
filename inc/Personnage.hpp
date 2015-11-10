#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>
#include <AliveEntity.hpp>

/**
* \file Personnage.hpp
* \brief Gère l'ensemble des outils neccessaires à
*	     l'éxécution des différentes méthodes du personnage.
* \author {N. Guittonneau,P. Raballand}
* \version 1.0
* \date 29/10/2015
*
* Gère toutes les méthodes d'un personnage
*/

/**
* \class Personnage
* \brief Classe définissant un personnage.
*/
class Personnage : public AliveEntity
{
public:
	/**
	* \brief Constructeur
	*
	* Constructeur de la classe Personnage.
	*
	* \param taille : taille (en 2D) du personnage.
	*/
	Personnage(const sf::Vector2f &taille);

	/**
	* \brief Destructeur
	*
	* Destructeur de la classe Personnage.
	*/
	~Personnage();

	/**
	* \fn void addMouvement(const sf::Vector2f & mvt);
	* \brief Modifie le mouvement en cours, en vérifiant qu'il reste
	*		 dans des limites définies
	*
	* Modifie le mouvement du personnage en fonction des anciens paramètres
	* et des limites fixées par le jeu.
	*
	* \param v : vecteur 2 dimensions qui affectera le mouvement en cours
	*/
	void addMouvement(const sf::Vector2f &mvt);

	/**
	* \fn void move(sf::Vector2f v)
	* \brief Bouge le Personnage
	*
	* Déplace le Personnage en lui appliquant les frottements
	*
	* \param v : Vector2f définissant le mouvement.
	*/
	void move(sf::Vector2f v);

	void restartClock();
	sf::Time getElapsedTime() const;

private:
	sf::Clock _clock;
};


#endif
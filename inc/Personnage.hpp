#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>

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
class Personnage
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
	* \fn sf::Vector2f getMouvement()
	* \brief Getter du Mouvement du Personnage.
	*
	* Fonction retournant le prochain déplacement de x et en y du personnage.
	*
	* \return Un Vector2f équivalent au prochain mouvement du Personnage
	*/
	sf::Vector2f getMouvement();

	/**
	* \fn void setMouvement(sf::Vector2f v)
	* \brief Setter du Mouvement du Personnage.
	*
	* Méthode permettant de donner un mouvement défini (2D) à un personnage.
	*
	* \param v : vecteur 2 dimensions qui définira le nouveau mouvement 
	*/
	void setMouvement(sf::Vector2f v);

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
	* \fn sf::RectangleShape getShape() const
	* \brief Getter de la RectangleShape du Personnnage.
	*
	* Récupère le rectangle correspondant à la taille du personnage (contour)
	* Utile notamment pour les collisions/déplacements.
	*
	* \return La RectangleShape du Personnage
	*/
	sf::RectangleShape getShape() const;

	/**
	* \fn void setPosition(sf::Vector2f v)
	* \brief Setter de la position
	*
	* Initialiste la position du personnage.
	*
	* \return Vector2f correspondant au nouveau mouvement.
	*/
	void setPosition(sf::Vector2f v);

	/**
	* \fn void move(sf::Vector2f v)
	* \brief Bouge le Personnage
	*
	* Déplace le Personnage en lui appliquant les frottements
	*
	* \param v : Vector2f définissant le mouvement.
	*/
	void move(sf::Vector2f v);

private:
	sf::Vector2f _mouvement; /** Prochain mouvement */
	sf::RectangleShape _shape; /** HitBox du Personnage */
};


#endif
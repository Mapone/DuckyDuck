#ifndef ALIVEENTITY_H
#define ALIVEENTITY_H

#include <SFML/Graphics.hpp>

class AliveEntity
{
public:

	AliveEntity(const sf::Vector2f &taille);
	
	/**
	* \fn sf::Vector2f getMouvement()
	* \brief Getter du Mouvement de l'entité.
	*
	* Fonction retournant le prochain déplacement de x et en y de l'entité.
	*
	* \return Un Vector2f équivalent au prochain mouvement de l'entité
	*/
	sf::Vector2f getMouvement();

	/**
	* \fn void setMouvement(sf::Vector2f v)
	* \brief Setter du Mouvement de l'entité.
	*
	* Méthode permettant de donner un mouvement défini (2D) à un personnage.
	*
	* \param v : vecteur 2 dimensions qui définira le nouveau mouvement 
	*/
	void setMouvement(sf::Vector2f v);

	/**
	* \fn sf::RectangleShape getShape() const
	* \brief Getter de la RectangleShape de l'entité.
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


protected:
	sf::Vector2f _mouvement; /** Prochain mouvement */
	sf::RectangleShape _shape; /** HitBox du Personnage */
};


#endif
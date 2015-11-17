#ifndef ALIVEENTITY_H
#define ALIVEENTITY_H

#include <SFML/Graphics.hpp>


/**
* \file AliveEntity.hpp
* \brief Classe définissant les objets "vivants"
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 14/11/2015
*
* Définit les méthodes communes à tout les objets "vivants"
*/

/**
* \class AliveEntity
* \brief Classe abstraite qui définissant les objets "vivants"
*
* Classe abstraite qui définit les méthodes des Enemy et du Personnage.
*/
class AliveEntity
{
public:

	/**
	* \brief Constructeur
	* 
	* Constructeur de la classe AliveEntity
	*
	* \param taille : taille de l'objet.
	*/
	AliveEntity(const sf::Vector2f &taille);
	
	/**
	* \fn sf::Vector2f getMouvement()
	* \brief Getter du Mouvement de l'entité.
	*
	* Fonction retournant le prochain déplacement de x et en y de l'entité.
	*
	* \return Un Vector2f équivalent au prochain mouvement de l'entité
	*/
	sf::Vector2f getMouvement() const;

	/**
	* \fn void setMouvement(sf::Vector2f v)
	* \brief Setter du Mouvement de l'entité.
	*
	* Méthode permettant de donner un mouvement défini (2D) à un objet.
	*
	* \param v : vecteur 2 dimensions qui définira le nouveau mouvement 
	*/
	void setMouvement(sf::Vector2f v);

	/**
	* \fn void addMouvement(const sf::Vector2f &mvt)
	* \brief Incrémente le mouvement de l'objet.
	*
	* Ajoute au vector déjà existant un nouveau mouvement.
	*
	* \param mvt : mouvement à ajouter.
	*/
	void addMouvement(const sf::Vector2f &mvt);

	/**
	* \fn void addMouvement(float x, float y)
	* \brief Incrémente le mouvement de l'objet.
	*
	* Ajoute au vector déjà existant un nouveau mouvement.
	*
	* \param x : mouvement en x, y : mouvement en y.
	*/
	void addMouvement(float x, float y);

	/**
	* \fn sf::RectangleShape getShape() const
	* \brief Getter de la RectangleShape de l'entité.
	*
	* Récupère le rectangle correspondant à la taille de l'objet (contour)
	* Utile notamment pour les collisions/déplacements.
	*
	* \return La RectangleShape de l'objet
	*/
	sf::RectangleShape getShape() const;


	/**
	* \fn void setPosition(sf::Vector2f v)
	* \brief Setter de la position
	*
	* Initialiste la position de l'objet.
	*
	* \param v : Vector correspondant aux coordonnées.
	*/
	void setPosition(sf::Vector2f v);

	/**
	* \fn void setPosition(float x, float y)
	* \brief Setter de la position
	*
	* Initialiste la position de l'objet.
	*
	* \param x : coordonnée en x, y : coordonnée en y.
	*/
	void setPosition(float x, float y);

	/**
	 * @brief Setter de la taille
	 * @details Setter de la taille
	 * 
	 * @param x Nouvelle taille en x
	 * @param y Nouvelle taille en y
	 */
	void setSize(float x, float y);


	/**
	* \fn const sf::Vector2f & getPosition() const
	* \brief Getter de la position
	*
	* Récupère la position de l'objet
	*
	* \return Vector2f équivalent à la position de l'objet
	*/
	const sf::Vector2f & getPosition() const;

	/**
	* \fn const sf::Vector2f & getSize() const
	* \brief Getter de la Size
	*
	* Récupère la taille de l'objet
	*
	* \return Vector2f équivalent à la taille de l'objet
	*/
	const sf::Vector2f & getSize() const;


protected:
	sf::Vector2f _mouvement; /** Prochain mouvement */
	sf::RectangleShape _shape; /** HitBox de l'objet */
};

#endif
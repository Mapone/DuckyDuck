#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>
#include <AliveEntity.hpp>

/**
* \file Personnage.hpp
* \brief Gère l'ensemble des outils neccessaires à
*	     l'éxécution des différentes méthodes du personnage.
* \author {N. Guittonneau,P. Raballand}
* \version 1.1
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
	* \param taille : taille (en 2D) du personnage, i : image du personnage, t : texture du personnage.
	*/
	Personnage(const sf::Vector2f &taille, sf::Image &i, sf::Texture &t);

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

	/**
	* \fn void restartClock()
	* \brief relance la clock du personnage
	*
	* Appelle un fonction de SFML qui reset la clock.
	*/
	void restartClock();

	/**
	* \fn sf::Time getElapsedTime() const
	* \brief Récupère le temps écoulé
	*
	* Retourne le temps passé depuis
	* la dernière ré-initialisation de la clock
	*
	* \return La durée qui s'est écoulé depuis le début du niveau
	*/
	sf::Time getElapsedTime() const;

	/**
	* \fn void flipRight()
	* \brief Tourne la texture vers la droite
	*
	* Fait regarder le canard à droite
	*/
	void flipRight();
	
	/**
	* \fn void flipLeft()
	* \brief Tourne la texture à gauche
	*
	* Fait regarder le canard à gauche
	*/
	void flipLeft();

	/**
	* \fn unsigned int getCurrentKill() const
	* \brief Getter de CurrentKill
	*
	* Récupère le nombre de kill fait par le personnage
	* sur le niveau en cours
	*
	* \return Le nombre de kill
	*/
	unsigned int getCurrentKill() const;

	/**
	* \fn unsigned int getCurrentScore() const
	* \brief Getter de CurrentScore
	*
	* Récupère le score fait par le personnage
	* sur le niveau en cours
	*
	* \return Le score
	*/
	unsigned int getCurrentScore() const;

	/**
	* \fn unsigned int getTotalKill() const
	* \brief Getter de TotalKill
	*
	* Récupère le nombre de kill fait par le personnage
	* sur la totalité des niveaux
	*
	* \return Le nombre de kill total
	*/
	unsigned int getTotalKill() const;

	/**
	* \fn unsigned int getTotalScore() const
	* \brief Getter de TotalScore
	*
	* Récupère le  score fait par le personnage
	* sur la totalité des niveaux
	*
	* \return Le score total
	*/
	unsigned int getTotalScore() const;

	/**
	* \fn void setCurrentKill(unsigned int k)
	* \brief Setter de CurrentKill
	*
	* Initialise le nombre de kill
	*
	* \param k : valeur d'initialisation
	*/
	void setCurrentKill(unsigned int k);

	/**
	* \fn void setCurrentScore(unsigned int s)
	* \brief Setter de CurrentScore
	*
	* Initialise le score
	*
	* \param s : valeur d'initialisation
	*/
	void setCurrentScore(unsigned int s);

	/**
	* \fn void setTotalKill(unsigned int k)
	* \brief Setter de TotalKill
	*
	* Initialise le nombre de total de kill
	*
	* \param k : valeur d'initialisation
	*/
	void setTotalKill(unsigned int k);

	/**
	* \fn void setTotalScore(unsigned int s)
	* \brief Setter de TotalScore
	*
	* Initialise le score total
	*
	* \param s : valeur d'initialisation
	*/
	void setTotalScore(unsigned int s);


private:
	sf::Clock _clock; /** Clock gérer par SFML */
	sf::Image _imgDuck; /** Image du personnage */
	sf::Texture _textureDuck; /** Texture créer par l'image */
	bool _lookRight; /** Direction D/G vers ou le personnage est touné */
	unsigned int _currentScore; /** Score temporaire du personnage*/
	unsigned int _currentKill; /** Nombre d'enemis tué temporaire du personnage */
	unsigned int _totalScore; /** Score total du personnage */
	unsigned int _totalKill; /** Nombre total d'ennemis tués */
};


#endif
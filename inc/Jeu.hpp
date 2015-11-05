#ifndef JEU_H
#define JEU_H

#include <SFML/Graphics.hpp>

/**
* \file Jeu.hpp
* \brief Gère l'ensemble des outils permettant d'effectuer
*        une partie de DuckyDuck.
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 28/10/2015
*
* Gère tout la fenêtre et les interactions lors d'une partie
*/

class TileMap;
class Personnage;
class State;
class StateMainMenu;
class StateEscMenu;
class StateLevel;
class StateStats;

/**
* \class Jeu
* \brief Gère tout la fenêtre et les interactions lors d'une partie
*/
class Jeu : public sf::Drawable, public sf::Transformable
{
public:

	/**
	* \brief Constructeur
	*
	* Constructeur de la classe Jeu
	*
	* \param t : TileMap à générer, p : Personnage à jouer.
	*/
	Jeu(TileMap &t, Personnage &p);

	/**
    * \brief Destructeur
    *
    *  Destructeur de la classe Jeu
    */
	~Jeu();

	void start();

	/**
	* \fn void Jeu::addLevel(TileMap t)
	* \brief Ajout d'un niveau au Jeu.
	*
	* Méthode permettant d'ajouter un level depuis une TileMap au Jeu.
	*
	* \param t : La TileMap à ajouter comme niveau.
	*/
	void addLevel(TileMap* t);

	/**
	* \fn TileMap* getCurrentLevel() const
	* \brief Récupère le niveau en cours
	*
	* Fonction permettant de récupérer la TileMap du niveau en cours
	*/
	TileMap* getCurrentLevel() const;

	/**
	* \fn const sf::Font& getFont() const
	* \brief Récupère le Font rattachée
	*
	* Récupère la police rattaché au Jeu.
	*/
	const sf::Font& getFont() const;

	/**
	* \fn void setState(State* s)
	* \brief Setter du State
	*
	* Permet de modifier l'état du State.
	*
	* \param s : State à modifier.
	*/
	void setState(State* s);

	/**
	* \fn StateLevel* getStateLevel() const
	* \brief Getter du StateLevel
	*
	* Renvoi le StateLevel
	*
	* \return Un StateLevel
	*/
	StateLevel* getStateLevel() const;

	/**
	* \fn StateEscMenu* getStateEscMenu() const
	* \brief Getter du StateEscMenu
	*
	* Renvoi le StateEscMenu
	*
	* \return Un StateEscMenu
	*/
	StateEscMenu* getStateEscMenu() const;
	StateMainMenu* getStateMainMenu() const;
	StateStats* getStateStats(bool IsLevelFinished) const;


	void initStateLevel() const;
	bool changeToNextLevel();



	/**
	* \fn void close()
	* \brief Enregistre la fermeture de la fenêtre
	*
	* Passe un global bool en false afin d'enregistrer
	* la fermeture de la fenêtr principale.
	*/
	void close();

	void restartCharClock() const;



private:

	/**
	* \fn virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	* \brief Appel la création du personnage, et gère les actions utilisateurs.
	*
	* Affiche le personnage et lui applique les actions correspondantes. 
	*
	* \param target : objet à afficher, states : ???
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	/**
	* \fn void input()
	* \brief Fonction qui attends les entrées et appelle les différentes méthodes.
	*
	* Gère les entrées utilisateurs et appelle ensuite la fonction rattachée.
	*
	*/
	void input();

	bool isOpen; /** Informe sur l'état de la fenêtre (open/close) */
	std::vector<TileMap*> _levels; /** Vecteur de tous les niveaux */
	unsigned int _currentLevel; /** Niveau en cours */
	Personnage &_perso; /** Personnage joué */
	sf::Font _font; /** Police d'écriture */
	State* _currentState; /** Etat actuel */
	StateMainMenu* _stateMainMenu; /** Etat Menu Principal */
	StateEscMenu* _stateEscMenu; /** Etat Menu en Partie */
	StateStats* _stateStats; /** Etat Menu statistiques */
	StateLevel* _stateLevel; /** Etat en jeu */
};

#endif
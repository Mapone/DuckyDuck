#ifndef STATELEVEL_H
#define STATELEVEL_H

/**
* \file StateLevel.hpp
* \brief Etat en jeu
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 3/11/2015
*
* Etat StateLevel rattaché au Pattern State
*/

#include <SFML/Graphics.hpp>
#include "State.hpp"
class TileMap;
class Jeu;
class Personnage;

/**
* \classe StateLevel
* \brief Etat StateLevel rattaché au Pattern State
*/
class StateLevel : public State
{
public:

  /**
  * \brief Constructeur
  *
  * Constructeur de la classe State
  * 
  * \param jeu : Jeu sur lequel le Pattern State s'applique, perso : Personnage jouable
  */
  StateLevel(Jeu* jeu, TileMap* tilemap, Personnage& perso);

  /**
  * \fn virtual void draw(sf::RenderTarget& target, st::RenderStates states) const
  * \brief Dessine un objet
  * 
  * Prends un objet target et le dessine.
  *
  * \param target : objet à dessiner, states : applique la transformation (SFML Function)
  */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  /**
  * \fn virtual void init()
  * \brief initialise les coord. du spawn du personnage
  *
  * Initialise pour les niveaux les coordonnées du Personnage jouable.
  */
  virtual void init();

  /**
  * \fn virtual void setLevel(TileMap* t)
  * \brief Setter de la TileMap.
  *
  * Initialise la TileMap du level, et l'initialise
  *
  * \param t : la nouvelle TileMap
  */
  virtual void setLevel(TileMap* t);

  /**
  * \fn virtual void pressSpace() = 0;
  * \brief Action à effectuer quand Espace est appuyé
  *
  * Gère les actions rattachées à la barre d'espace.
  */
  virtual void pressSpace();

  /**
  * \fn virtual void pressUp() = 0;
  * \brief Action à effectuer quand la touche Haut est appuyé
  *
  * Gère les actions rattachées à la touche Haut.
  */
  virtual void pressUp();

  /**
  * \fn virtual void pressDown() = 0;
  * \brief Action à effectuer quand la touche Bas est appuyé
  *
  * Gère les actions rattachées à la touche Bas.
  */
  virtual void pressDown();

  /**
  * \fn virtual void pressEsc() = 0;
  * \brief Action à effectuer quand la touche Echap est appuyé
  *
  * Gère les actions rattachées à la touche Echap.
  */
  virtual void pressEsc();

  /**
  * \fn virtual void pressLeft() = 0;
  * \brief Action à effectuer quand la touche Gauche est appuyé
  *
  * Gère les actions rattachées à la touche Gauche.
  */
  virtual void pressLeft();

  /**
  * \fn virtual void pressRight() = 0;
  * \brief Action à effectuer quand la touche Droite est appuyé
  *
  * Gère les actions rattachées à la touche Droite.
  */
  virtual void pressRight();

  void update();

private:

  TileMap* _tilemap; /** TileMap du niveau */
  Personnage& _perso; /** Personnage jouable */

  /**
  * \fn void checkMapCollision() const
  * \brief Vérifie les collisions et agit en conséquence
  *
  * Vérifie si le Personnage jouable est en collision avec le niveau
  * et agit en conséquence.
  */
  void checkMapCollision() const;

  /**
  * \fn void updateCamera() const
  * \brief update la caméra
  */
  void updateCamera() const;

  /**
   * @brief Collisions globales entre toutes les entités et le personnage
   * @details Vérification et application des conséquences en cas de collisions entre le personnage et chaque ennemis (appel de collisionEnemy) et le bloc fin de niveau
   */
  void checkCollision();

  /**
  * \fn bool checkCollision(const sf::RectangleShape& s1, const sf::RectangleShape& s2) const
  * \brief Vérifie la collision entre 2 objets
  *
  * Vérifie s'il existe une collision entre deux objets
  *
  * \param s1 : objet 1, s2 : objet 2
  * \return L'état de la collision
  */
  bool checkCollision(const sf::RectangleShape& s1, const sf::RectangleShape& s2) const;

  /**
  * \fn bool collisionEnemy() const
  * \brief Vérifie la collision entre le personnage et tous les ennmis
  *
  * Vérifie s'il existe une collision entre les ennemis et notre personnage
  *
  * \return L'état de la collision
  */
  bool collisionEnemy() const;

  /**
  * \fn bool collisionEnemy(Enemy *e) const
  * \brief Vérifie la collision entre le personnage un ennemi
  *
  * Vérifie s'il existe une collision entre un ennemi et notre personnage
  *
  *\param *e : l'ennemi à tester 
  * \return L'état de la collision
  */
  bool collisionEnemy(Enemy *e) const;

  /**
  * \fn void enemyMove() const
  * \brief Fait bouger tout les ennemis et verifie leur collision avec le perso
  *
  * Appelle la fonction move de tout les Enemy de la TileMap verifie leur collision avec le perso
  */
  void enemyMove() const;


};

#endif

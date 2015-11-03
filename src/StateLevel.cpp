#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateLevel.hpp"
#include "StateEscMenu.hpp"

using namespace std;

const unsigned int LARGEUR_FENETRE = 800;
const unsigned int HAUTEUR_FENETRE = 448;
const unsigned int TAILLE_TUILE = 16;


StateLevel::StateLevel(Jeu* jeu, TileMap& tilemap, Personnage& perso) : State(jeu), _tilemap(tilemap), _perso(perso)
{}

void  StateLevel::init()
{
	_perso.setPosition(sf::Vector2f(10,10));
}

void StateLevel::update() const
{
	checkMapCollision();
    updateCamera();
}

void StateLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	(void)states;
	update();
	target.draw(_tilemap);
	target.draw(_perso.getShape());
}

void StateLevel::pressUp()
{
	pressSpace();
}

void StateLevel::pressDown(){}
void StateLevel::pressLeft()
{
	_perso.addMouvement(sf::Vector2f(-0.2,0));
}

void StateLevel::pressRight()
{
	_perso.addMouvement(sf::Vector2f(0.2,0));
}

void StateLevel::pressSpace()
{
    if(_tilemap.collisionBas(_perso.getShape(),sf::Vector2f(_perso.getMouvement().x,1)))
    	_perso.addMouvement(sf::Vector2f(0,-20));
}

void StateLevel::pressEsc()
{
    _jeu->setState(_jeu->getStateEscMenu());
}

void StateLevel::checkMapCollision() const
{
    //On applique d'abord la gravité au personnage
    _perso.addMouvement(_tilemap.getGravity());

    //On initialise des vecteurs pour limiter le nombre d'appels sur _perso
    sf::Vector2f position = _perso.getShape().getPosition();
    sf::Vector2f size = _perso.getShape().getSize();
    sf::Vector2f mvt = _perso.getMouvement();

    bool colHaut, colBas, colGauche, colDroite;
    bool colXHautGauche, colXHautDroit, colXBasGauche, colXBasDroit; 
    bool colYHautGauche, colYHautDroit, colYBasGauche, colYBasDroit;

    //On calcule la collision en X et en Y pour chacun des 4 points de notre rectangleShape
    colXHautGauche = _tilemap.collision(position, sf::Vector2f(mvt.x,0));
    colXHautDroit = _tilemap.collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(mvt.x,0));
    colXBasGauche = _tilemap.collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(mvt.x,0));
    colXBasDroit = _tilemap.collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(mvt.x,0));

    colYHautGauche = _tilemap.collision(position, sf::Vector2f(0,mvt.y));
    colYHautDroit = _tilemap.collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(0,mvt.y));
    colYBasGauche = _tilemap.collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(0,mvt.y));
    colYBasDroit = _tilemap.collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(0,mvt.y));

    //On en déduit les collision des cotés 
    colHaut = colYHautDroit || colYHautGauche;
    colBas = colYBasDroit || colYBasGauche;
    colGauche = colXBasGauche || colXHautGauche;
    colDroite = colXHautDroit || colXBasDroit;

    //On cherche d'ou viens la collision
    if(colGauche || colDroite)
        _perso.setMouvement(sf::Vector2f(0,_perso.getMouvement().y));

    if(colHaut || colBas)
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));

    _perso.move();
}

void StateLevel::updateCamera() const
{
    //On définit un rectangle invisible au milieu de l'ecran
    //Si le personnage arrive sur le bord de celui ci, il faut bouger la camera (ce qui revient à deplacer la map)
    //Collision à droite 

    using namespace std;

    if(_perso.getShape().getPosition().x >= LARGEUR_FENETRE - 200 && fabs(_tilemap.getPosition().x) + LARGEUR_FENETRE <  _tilemap.getWidth() * TAILLE_TUILE)
    {
        _tilemap.setPosition(_tilemap.getPosition().x - _perso.getMouvement().x, _tilemap.getPosition().y);
        _perso.setPosition(sf::Vector2f(LARGEUR_FENETRE - 200, _perso.getShape().getPosition().y));
    }
    //Collision à gauche
    else if(_perso.getShape().getPosition().x <= 200 && _tilemap.getPosition().x < 0)
    {
        _tilemap.setPosition(_tilemap.getPosition().x - _perso.getMouvement().x, _tilemap.getPosition().y);
        _perso.setPosition(sf::Vector2f(200, _perso.getShape().getPosition().y));
    }
}
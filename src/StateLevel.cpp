#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateLevel.hpp"

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
    //On cherche d'ou viens la collision
    if(_tilemap.collisionBas(_perso.getShape(), _perso.getMouvement()) ||
       _tilemap.collisionHaut(_perso.getShape(), _perso.getMouvement()))
    {
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));
    }

    if(_tilemap.collisionDroite(_perso.getShape(),_perso.getMouvement()) ||
       _tilemap.collisionGauche(_perso.getShape(),_perso.getMouvement()))
    {

        _perso.setMouvement(sf::Vector2f(0,_perso.getMouvement().y));
    }

    //Si pas de colision en bas, on applique la gravité
    if(!_tilemap.collisionBas(_perso.getShape(), sf::Vector2f(_perso.getMouvement().x,1)))
    {        
        _perso.addMouvement(_tilemap.getGravity());
    }
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
        _perso.move(sf::Vector2f(-0.1, _perso.getMouvement().y));
    }
    //Collision à gauche
    else if(_perso.getShape().getPosition().x <= 200 && _tilemap.getPosition().x < 0)
    {
        _tilemap.setPosition(_tilemap.getPosition().x - _perso.getMouvement().x, _tilemap.getPosition().y);
        _perso.move(sf::Vector2f(0.1, _perso.getMouvement().y));
    }
    else
    {
        _perso.move();
    }
}
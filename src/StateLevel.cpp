#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateLevel.hpp"

using namespace std;

StateLevel::StateLevel(Jeu* jeu, TileMap& tilemap, Personnage& perso) : State(jeu), _tilemap(tilemap), _perso(perso)
{}

void  StateLevel::init()
{
	_perso.setPosition(sf::Vector2f(10,10));
}

void StateLevel::update() const
{
	checkMapCollision();
	_perso.move();
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
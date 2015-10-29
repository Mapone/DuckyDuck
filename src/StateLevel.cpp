#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateLevel.hpp"

using namespace std;

StateLevel::StateLevel(Jeu* jeu, TileMap& tilemap, Personnage& perso) : State(jeu), _tilemap(tilemap), _perso(perso)
{
	cout <<"Dans le constru: "<< &_perso << endl;
}

void  StateLevel::init()
{
	_perso.setPosition(sf::Vector2f(10,10));
}

void StateLevel::update()
{
}

void StateLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	(void)states;
	_jeu->checkCollision();
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

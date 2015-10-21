#include <iostream>
#include <SFML/Graphics.hpp>
#include "Personnage.hpp"

using namespace sf;

const int MAX_SPEED_X = 3;
const int MAX_SPEED_Y = 5;
const float FROTTEMENTS = 0.08;

Personnage::Personnage(const Vector2f &taille)
{
	_perso.setSize(taille);
	_mouvement = Vector2f(0,0);
}
Personnage::~Personnage(){}


Vector2f Personnage::getMouvement()
{
	return _mouvement;
}

void Personnage::setMouvement(sf::Vector2f v)
{
	_mouvement = v;
}

void Personnage::addMouvement(const Vector2f &mvt)
{
	if(_mouvement.x + mvt.x <= MAX_SPEED_X)
	{
		if(_mouvement.x + mvt.x >= -MAX_SPEED_X)
			_mouvement.x += mvt.x;
		else
		_mouvement.x = -MAX_SPEED_X;
	}
	else
		_mouvement.x = MAX_SPEED_X;

	//
	if(_mouvement.y + mvt.y <= MAX_SPEED_Y)
	{
		if(_mouvement.y + mvt.y >= -MAX_SPEED_Y)
			_mouvement.y += mvt.y;
		else
		_mouvement.y = -MAX_SPEED_Y;
	}
	else
		_mouvement.y = MAX_SPEED_Y;

	//Si il y a un mouvement vers le bas (chute ou application de la gravité, on applique des frottements sur x)
	if(_mouvement.x>0)
	{
		if(_mouvement.x - FROTTEMENTS < 0)
			_mouvement.x = 0;
		else
			_mouvement.x -= FROTTEMENTS; 
	}

	if(_mouvement.x<0)
	{
		if(_mouvement.x + FROTTEMENTS > 0)
			_mouvement.x = 0;
		else
			_mouvement.x += FROTTEMENTS; 
	}
}

sf::RectangleShape& Personnage::getPerso()
{
	return _perso;
} 

//Applique le vecteur de mouvement à la RectangleShape du personnage 
void Personnage::move()
{
	_perso.setPosition(_perso.getPosition()+_mouvement);
}


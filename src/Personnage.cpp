#include <iostream>
#include "Personnage.hpp"

using namespace sf;

const int MAX_SPEED_X = 3;
const int MAX_SPEED_Y = 5;
const float FROTTEMENTS = 0.08;

Personnage::Personnage(const Vector2f &taille) : AliveEntity(taille)
{}
Personnage::~Personnage(){}

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

}

void Personnage::move(sf::Vector2f v)
{
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

	_shape.setPosition(_shape.getPosition()+v);
}

void Personnage::restartClock()
{
	_clock.restart();
}

sf::Time Personnage::getElapsedTime() const
{
	return _clock.getElapsedTime();
}
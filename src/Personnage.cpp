#include <iostream>
#include "Personnage.hpp"

using namespace sf;
using namespace std;

const int MAX_SPEED_X = 3;
const int MAX_SPEED_Y = 5;
const float FROTTEMENTS = 0.1;

Personnage::Personnage(const Vector2f &taille, Image &i, Texture &t) : AliveEntity(taille), _imgDuck(i), _textureDuck(t)
{
	_textureDuck.loadFromImage(_imgDuck);
	_shape.setTexture(&_textureDuck, true);
	_textureDuck.update(_imgDuck);
	_lookRight = true;
	_currentScore = 0;
	_currentKill = 0;
	_totalScore = 0;
	_totalKill = 0;
}
Personnage::~Personnage(){}

void Personnage::addMouvement(const Vector2f &mvt)
{
/*
	cout << "MOVE param "<< mvt.x << ":" << mvt.y << endl;
	cout << "MOVE OP en y"<< mvt.y + _mouvement.y << endl;
	cout << "MOVE AVANT "<< getMouvement().x << ":" << getMouvement().y << endl;*/


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

	/*cout << "MOVE APRES "<< getMouvement().x << ":" << getMouvement().y << endl;
	cout << endl;*/
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

void Personnage::flipRight()
{
	if(!_lookRight)
	{
		_imgDuck.flipHorizontally();
		_textureDuck.update(_imgDuck);
		_lookRight = true;
	}
}

void Personnage::flipLeft()
{
	if(_lookRight)
	{
		_imgDuck.flipHorizontally();
		_textureDuck.update(_imgDuck);
		_lookRight = false;
	}
}

unsigned int Personnage::getCurrentKill() const
{
	return _currentKill;
}
unsigned int Personnage::getCurrentScore() const
{
	return _currentScore;
}
unsigned int Personnage::getTotalKill() const
{
	return _totalKill;
}
unsigned int Personnage::getTotalScore() const
{
	return _totalScore;
}
void Personnage::setCurrentKill(unsigned int k)
{
	_currentKill = k;
}
void Personnage::setCurrentScore(unsigned int s)
{
	_currentScore = s;
}
void Personnage::setTotalKill(unsigned int k)
{
	_totalKill = k;
}
void Personnage::setTotalScore(unsigned int s)
{
	_totalScore = s;
}
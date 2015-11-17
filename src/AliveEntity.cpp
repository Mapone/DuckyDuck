#include <iostream>
#include "AliveEntity.hpp"

AliveEntity::AliveEntity(const sf::Vector2f &taille)
{
	_shape.setSize(taille);
	_mouvement = sf::Vector2f(0,0);
}

sf::Vector2f AliveEntity::getMouvement() const
{
	return _mouvement;
}

void AliveEntity::setMouvement(sf::Vector2f v)
{
	_mouvement = v;
}

void AliveEntity::addMouvement(const sf::Vector2f &mvt)
{
	_mouvement += mvt;
}

void AliveEntity::addMouvement(float x, float y)
{
	_mouvement.x += x;
	_mouvement.y += y;
}

sf::RectangleShape AliveEntity::getShape() const
{
	return _shape;
}

void AliveEntity::setPosition(sf::Vector2f v)
{
	_shape.setPosition(v);
}

void AliveEntity::setPosition(float x, float y)
{
	_shape.setPosition(sf::Vector2f(x,y));
}

void AliveEntity::setSize(float x, float y)
{
	_shape.setSize(sf::Vector2f(x,y));
}

const sf::Vector2f & AliveEntity::getPosition() const
{
	return _shape.getPosition();
}

const sf::Vector2f & AliveEntity::getSize() const
{
	return _shape.getSize();
}


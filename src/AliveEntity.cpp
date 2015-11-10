#include <iostream>
#include "AliveEntity.hpp"


AliveEntity::AliveEntity(const sf::Vector2f &taille)
{
	_shape.setSize(taille);
	_mouvement = sf::Vector2f(0,0);
}

sf::Vector2f AliveEntity::getMouvement()
{
	return _mouvement;
}

void AliveEntity::setMouvement(sf::Vector2f v)
{
	_mouvement = v;
}

sf::RectangleShape AliveEntity::getShape() const
{
	return _shape;
}

void AliveEntity::setPosition(sf::Vector2f v)
{
	_shape.setPosition(v);
}


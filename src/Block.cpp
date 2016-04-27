#include <iostream>
#include "Block.hpp"

using namespace std;

Block::Block(const sf::Vector2f &size)
{
	_shape.setSize(size);
}

void Block::flipBlock()
{}

sf::RectangleShape Block::getShape() const
{
	return _shape;
}

const sf::Vector2f & Block::getPosition() const
{
	return _shape.getPosition();
}

void Block::setPosition(float x, float y)
{
	_shape.setPosition(sf::Vector2f(x,y));
}

void Block::setPosition(sf::Vector2f v)
{
	_shape.setPosition(v);
}

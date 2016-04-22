#include <iostream>
#include "InvertGravityBlock.hpp"

using namespace std;

InvertGravityBlock::InvertGravityBlock(const sf::Vector2f &size)
{
	if(!_arrowUp.loadFromFile("arrowUp.png"))
		cerr << "#ERROR arrowUP.png failed" << endl;

	if(!_arrowDown.loadFromFile("arrowDown.png"))
		cerr << "#ERROR arrowDown.png failed" << endl;

	_shape.setSize(size);
	_shape.setTexture(&_arrowUp, true);
	up = false;
}

void InvertGravityBlock::flipBlock()
{
	if(up)
		_shape.setTexture(&_arrowUp, true);
	else
		_shape.setTexture(&_arrowDown, true);
	up = !up;
}

sf::RectangleShape InvertGravityBlock::getShape() const
{
	return _shape;
}

void InvertGravityBlock::setPosition(sf::Vector2f v)
{
	_shape.setPosition(v);
}

const sf::Vector2f & InvertGravityBlock::getPosition() const
{
	return _shape.getPosition();
}

void InvertGravityBlock::setPosition(float x, float y)
{
	_shape.setPosition(sf::Vector2f(x,y));
}

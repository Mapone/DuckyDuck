#include <iostream>
#include "InvertGravityBlock.hpp"

using namespace std;

InvertGravityBlock::InvertGravityBlock(const sf::Vector2f &size) : Block(size)
{
	if(!_arrowUp.loadFromFile("arrowUp.png"))
		cerr << "#ERROR arrowUP.png failed" << endl;

	if(!_arrowDown.loadFromFile("arrowDown.png"))
		cerr << "#ERROR arrowDown.png failed" << endl;

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
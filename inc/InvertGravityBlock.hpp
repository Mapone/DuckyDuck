#ifndef INVERTGRAVITYBLOCK_H
#define INVERTGRAVITYBLOCK_H

#include <SFML/Graphics.hpp>
#include "Block.hpp"

class InvertGravityBlock : public Block
{
public:
	InvertGravityBlock(const sf::Vector2f &size);

	void flipBlock();

private:
	sf::Texture _arrowUp;
	sf::Texture _arrowDown;
	bool up;
};


#endif
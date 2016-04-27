#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Block
{
public:
	Block(const sf::Vector2f &size);

	void flipBlock();

	sf::RectangleShape getShape() const;

	void setPosition(sf::Vector2f v);

	void setPosition(float x, float y);

	const sf::Vector2f & getPosition() const;

protected:
	sf::RectangleShape _shape;
	sf::Texture _texture;
};


#endif
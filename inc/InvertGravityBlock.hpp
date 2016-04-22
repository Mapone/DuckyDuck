#ifndef INVERTGRAVITYBLOCK_H
#define INVERTGRAVITYBLOCK_H

#include <SFML/Graphics.hpp>

class InvertGravityBlock
{
public:
	InvertGravityBlock(const sf::Vector2f &size);

	void flipBlock();

	sf::RectangleShape getShape() const;

	void setPosition(sf::Vector2f v);

	void setPosition(float x, float y);

	const sf::Vector2f & getPosition() const;

private:
	sf::RectangleShape _shape;
	sf::Texture _arrowUp;
	sf::Texture _arrowDown;
	bool up;
};


#endif
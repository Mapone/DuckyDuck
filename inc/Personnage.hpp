#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>

class Personnage
{
public:
	Personnage(const sf::Vector2f &taille);
	~Personnage();
	sf::Vector2f getMouvement();
	void setMouvement(sf::Vector2f v);
	void addMouvement(const sf::Vector2f &mvt);
	sf::RectangleShape getShape() const;
	void setPosition(sf::Vector2f v);
	void move();

private:
	sf::Vector2f _mouvement;
	sf::RectangleShape _shape;
};


#endif
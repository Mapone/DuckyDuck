#ifndef PERSONNAGE_H
#define PERSONNAGE_H

class Personnage
{
public:
	Personnage(const sf::Vector2f &taille);
	~Personnage();
	sf::Vector2f getMouvement();
	void addMouvement(const sf::Vector2f &mvt);
	sf::RectangleShape & getPerso();
	void move();

private:
	sf::Vector2f _mouvement;
	sf::RectangleShape _perso;
};


#endif
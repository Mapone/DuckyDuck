#include <SFML/Graphics.hpp>
#include "Personnage.hpp"

using namespace sf;

Personnage::Personnage(const Vector2f &taille)
{
	_perso.setSize(taille);
}
Personnage::~Personnage(){}


Vector2f Personnage::getMouvement()
{
	return _mouvement;
}

void Personnage::setMouvement(const Vector2f &mvt)
{
	_mouvement.x += mvt.x; 
	_mouvement.y += mvt.y; 
}

sf::RectangleShape& Personnage::getPerso()
{
	return _perso;
} 

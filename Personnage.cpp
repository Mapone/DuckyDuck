#include <SFML/Graphics.hpp>
#include "Personnage.hpp"

Personnage::Personnage(Vector2f taille)
{
	_perso.setSize(taille);
}
Personnage::~Personnage()
{

}
Vecor2f Personnage::getMouvement()
{
	return _mouvement;
}

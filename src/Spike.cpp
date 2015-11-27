#include <iostream>
#include "Enemy.hpp"
#include "Personnage.hpp"
#include "Spike.hpp"

Spike::Spike(const sf::Vector2f taille, TileMap& tilemap): Enemy(taille, tilemap)
{
	_texture.loadFromFile("spike.png");
	_AI = NULL;
}


Enemy* Spike::clone()
{
	return new Spike(_shape.getSize(),_tileMap);
}

bool Spike::jumpOn()
{
	return true;	
}

//On redéfini la fonction move pour qu'elle n'appelle pas l'AI
void Spike::move()
{}

#include <iostream>
#include "Enemy.hpp"
#include "Personnage.hpp"
#include "Spike.hpp"

Spike::Spike(const sf::Vector2f taille, TileMap& tilemap): Enemy(taille, tilemap)
{
	if(!_img.loadFromFile("spike.png"))
		std::cerr << "#ERROR, fail to load duck.png" << std::endl;
	_img.flipVertically();
	_texture.loadFromImage(_img);
	_shape.setTexture(&_texture, true);
	_texture.update(_img);

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

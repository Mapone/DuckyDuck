#include "Enemy.hpp"
#include "Walker.hpp"
#include "AI_JumpRandom.hpp"

Walker::Walker(const sf::Vector2f &taille, const TileMap& tilemap) : Enemy(taille, tilemap)
{
	_shape.setFillColor(sf::Color::Red);
	_AI = new AI_JumpRandom(this, tilemap);
}

Enemy* Walker::clone()
{
	return new Walker(_shape.getSize(), _tileMap);
}
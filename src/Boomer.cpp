#include "Enemy.hpp"
#include "Boomer.hpp"
#include "AI_Boomer.hpp"

Boomer::Boomer(const sf::Vector2f &taille, const TileMap& tilemap, int fatPerFrame) : Enemy(taille, tilemap), _fatPerFrame(fatPerFrame)
{
	_shape.setFillColor(sf::Color::Green);
	_AI = new AI_Boomer(this, tilemap);
}

Enemy* Boomer::clone()
{
	return new Boomer(_shape.getSize(), _tileMap, _fatPerFrame);
}

unsigned int Boomer::getFatPerFrame() const
{
	return _fatPerFrame;
}

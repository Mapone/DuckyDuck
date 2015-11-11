#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "AI_LandBase.hpp"

Enemy::Enemy(const sf::Vector2f &taille, const TileMap& tilemap) : AliveEntity(taille)
{
	_shape.setFillColor(sf::Color::Red);
	_AI = new AI_LandBase(this, tilemap);
}

Enemy::~Enemy()
{
	delete _AI;
}

void Enemy::move()
{
	_AI->move();
}
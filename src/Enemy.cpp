#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "AI.hpp"

Enemy::Enemy(const sf::Vector2f &taille, const TileMap &tilemap) : AliveEntity(taille), _tileMap(tilemap) 
{}

Enemy::~Enemy()
{
	delete _AI;
}

void Enemy::move()
{
	_AI->move();
}
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "TileMap.hpp"
#include "AI.hpp"

Enemy::Enemy(const sf::Vector2f &taille, TileMap &tilemap) : AliveEntity(taille), _tileMap(tilemap) 
{}

Enemy::~Enemy()
{
	delete _AI;
}

void Enemy::move()
{
	_AI->move();
}

void Enemy::jumpOn()
{
	_tileMap.killEnemy(this);
}

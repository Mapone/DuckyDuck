#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "TileMap.hpp"
#include "AI.hpp"

Enemy::Enemy(const sf::Vector2f &taille, TileMap &tilemap) : AliveEntity(taille), _tileMap(tilemap), _isDead(false)
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
	_isDead = true;
}

unsigned int Enemy::getReward() const
{
	return 10;
}

bool Enemy::isDead()
{
	return _isDead;
}
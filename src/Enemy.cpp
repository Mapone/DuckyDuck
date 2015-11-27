#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "TileMap.hpp"
#include "AI.hpp"

Enemy::Enemy(const sf::Vector2f &taille, TileMap &tilemap) : AliveEntity(taille), _tileMap(tilemap), _isDead(false)
{
	_texture.loadFromFile("cat.png");
	_shape.setTexture(&_texture, true);
}

Enemy::~Enemy()
{
	delete _AI;
}

void Enemy::move()
{
	_AI->move();
}

bool Enemy::jumpOn()
{
	//Comportement par défaut quand on saute sur un ennemi, celui-ci meurt et ne tue pas le personnage (return false)
	_isDead = true;
	return false;
}

unsigned int Enemy::getReward() const
{
	return 10;
}

bool Enemy::isDead()
{
	return _isDead;
}
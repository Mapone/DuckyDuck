#include "iostream"
#include "Enemy.hpp"
#include "Follower.hpp"
#include "AI_Follower.hpp"
#include "TileMap.hpp"


Follower::Follower(const sf::Vector2f &taille,  TileMap& tilemap, const Personnage& perso, float speed, float jumpHeight) : Enemy(taille, tilemap), _perso(perso),_speed(speed), _jumpHeight(jumpHeight)
{
	_shape.setFillColor(sf::Color::Magenta);
	_AI = new AI_Follower(this, tilemap, perso);
}

Enemy* Follower::clone()
{
	return new Follower(_shape.getSize(), _tileMap, _perso, _speed, _jumpHeight);
}

float Follower::getSpeed() const
{
	return _speed;
}

float Follower::getJumpHeight() const
{
	return _jumpHeight;
}

unsigned int Follower::getReward() const
{
	return std::abs(_speed)*8 + _jumpHeight*3;
}

void Follower::jumpOn()
{
	_shape.setFillColor(sf::Color::Black);
}
#include "iostream"
#include "Enemy.hpp"
#include "Follower.hpp"
#include "AI_Follower.hpp"
#include "TileMap.hpp"

//Un follower doit connaitre le personnage pour pouvoir le suivre.
Follower::Follower(const sf::Vector2f &taille,  TileMap& tilemap, const Personnage& perso, float speed, float jumpHeight) : Enemy(taille, tilemap), _perso(perso),_speed(speed), _jumpHeight(jumpHeight)
{
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
	//Récompense basée sur la vitesse et la hauteur de saut du follower 
	return std::abs(_speed)*8 + _jumpHeight*3;
}

bool Follower::jumpOn()
{
	return false;
}
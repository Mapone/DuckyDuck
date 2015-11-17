#include "Enemy.hpp"
#include "Jumper.hpp"
#include "AI_Jumper.hpp"

Jumper::Jumper(const sf::Vector2f &taille, const TileMap& tilemap, int speed, int jumpHeight) : Enemy(taille, tilemap), _speed(speed), _jumpHeight(jumpHeight)
{
	_shape.setFillColor(sf::Color::Red);
	_AI = new AI_Jumper(this, tilemap);
}

Enemy* Jumper::clone()
{
	return new Jumper(_shape.getSize(), _tileMap, _speed, _jumpHeight);
}

int Jumper::getSpeed() const
{
	return _speed;
}

int Jumper::getJumpHeight() const
{
	return _jumpHeight;
}
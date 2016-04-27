#include <iostream>
#include <string>
#include "Enemy.hpp"
#include "Jumper.hpp"
#include "AI_Jumper.hpp"
#include "TileMap.hpp"


Jumper::Jumper(const sf::Vector2f &taille, TileMap& tilemap, int speed, int jumpHeight) : Enemy(taille, tilemap),_speed(speed), _jumpHeight(jumpHeight)
{
	std::string strImg = "Jumper.png";
	if(!_img.loadFromFile(strImg))
		std::cerr << "#ERROR, fail to load " << strImg << std::endl;
	_texture.loadFromImage(_img);
	_shape.setTexture(&_texture, true);
	_texture.update(_img);
	_AI = new AI_Jumper(this, tilemap);
}

Jumper::Jumper(const sf::Vector2f &taille, const sf::Vector2f &position,  TileMap& tilemap, int speed, int jumpHeight) : Enemy(taille, tilemap),_speed(speed), _jumpHeight(jumpHeight)
{
	_shape.setFillColor(sf::Color::Red);
	setPosition(position);
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

unsigned int Jumper::getReward() const
{
	return std::abs(_speed)*8 + _jumpHeight*3;
}
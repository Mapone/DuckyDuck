#include "Enemy.hpp"
#include "Boomer.hpp"
#include "AI_Boomer.hpp"
#include "Spawner.hpp"
#include "TileMap.hpp"
#include "Jumper.hpp"

Boomer::Boomer(const sf::Vector2f &taille, TileMap& tilemap, int fatPerFrame, Enemy* prototype) : Enemy(taille, tilemap), _fatPerFrame(fatPerFrame)
{
	_shape.setFillColor(sf::Color::Green);
	_AI = new AI_Boomer(this, tilemap);
	_prototype = prototype;
    _jumperSpawn = new Spawner(_prototype);
}

Boomer::~Boomer()
{
	delete _jumperSpawn;
}

Enemy* Boomer::clone()
{
	return new Boomer(_shape.getSize(), _tileMap, _fatPerFrame, _prototype);
}

unsigned int Boomer::getFatPerFrame() const
{
	return _fatPerFrame;
}

void Boomer::jumpOn()
{
	/*
	Enemy* tmp;

	tmp = _jumperSpawn->spawnEnemy();
	tmp->setPosition(getPosition());

	Enemy = */
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -2, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -1, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -0, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, 1, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, 2, 5));
	_tileMap.killEnemy(this);
}

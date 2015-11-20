#include <iostream>
#include "TileMap.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include "Spawner.hpp"

EnemySpawner::EnemySpawner(TileMap& tilemap, Enemy* enemy, float spawnfreq): Enemy (sf::Vector2f(15,15),tilemap), _tilemap(tilemap), _spawnfreq(spawnfreq)
{
	_shape.setFillColor(sf::Color::Black);
	_enemySpawn = new Spawner(enemy);
	_AI = NULL;
}

EnemySpawner::~EnemySpawner()
{
	delete _enemySpawn;
}

Enemy* EnemySpawner::clone()
{
	return new EnemySpawner(_tilemap, _enemySpawn->spawnEnemy(), _spawnfreq);
}

void  EnemySpawner::move()
{
	
	if (_clock.getElapsedTime().asSeconds() > _spawnfreq)
	{
		Enemy* e = _enemySpawn->spawnEnemy();
		e->setPosition(_shape.getPosition());
		_tilemap.addEnemy(e);
		_clock.restart();
	}	
}

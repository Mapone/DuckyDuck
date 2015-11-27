#include <iostream>
#include "TileMap.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include "Spawner.hpp"

EnemySpawner::EnemySpawner(TileMap& tilemap, Enemy* enemy, float spawnfreq): Enemy (sf::Vector2f(15,15),tilemap), _tilemap(tilemap), _spawnfreq(spawnfreq)
{
	_shape.setFillColor(sf::Color::Black);
	_enemySpawn = new Spawner(enemy);
	//Un spawner n'a pas d'AI
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
	//Comme il n'a pas d'AI, sa methode move est redéfinie
	if (_clock.getElapsedTime().asSeconds() > _spawnfreq)
	{
		Enemy* e = _enemySpawn->spawnEnemy();
		e->setPosition(_shape.getPosition());
		_tilemap.addEnemy(e);
		_clock.restart();
	}	
}

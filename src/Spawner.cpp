#include "Spawner.hpp"
#include "Enemy.hpp"

Spawner::Spawner(Enemy* prototype): prototype_(prototype)
{}

Enemy* Spawner::spawnEnemy()
{
	return prototype_->clone();
}


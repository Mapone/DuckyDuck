#include "AI.hpp"

AI::AI(Enemy* enemy, const TileMap& tilemap) : _tileMap(tilemap)
{
	_enemy = enemy;
}

AI::~AI(){}
void AI::move(){}
#include "AI.hpp"

AI::AI(Enemy* enemy, const TileMap& tilemap) : _enemy(enemy), _tileMap(tilemap)
{}

AI::~AI(){}
void AI::move(){}
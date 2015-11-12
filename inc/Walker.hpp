#ifndef WALKER_H
#define WALKER_H

#include "Enemy.hpp"

class TileMap;
class Walker : public Enemy
{
public:
	Walker(const sf::Vector2f &taille, const TileMap& tilemap);
	Enemy* clone();
};


#endif
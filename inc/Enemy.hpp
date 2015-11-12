#ifndef ENEMY_H
#define ENEMY_H

#include "AliveEntity.hpp"
class AI;
class TileMap;

class Enemy : public AliveEntity
{
public:
	Enemy(const sf::Vector2f &taille, const TileMap &tilemap);
	virtual ~Enemy();
	void move();
	virtual Enemy* clone() = 0;
protected:
	AI* _AI;
	const TileMap& _tileMap; //L'enemi doit avoir conscience de sa TileMap

};


#endif
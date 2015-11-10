#ifndef ENEMY_H
#define ENEMY_H

#include "AliveEntity.hpp"
#include "AI.hpp"

class Enemy : public AliveEntity
{
public:
	Enemy(const sf::Vector2f &taille);
	void move();
protected:
	AI* _AI;
};


#endif
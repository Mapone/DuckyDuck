#ifndef AI_JUMPRANDOM_H
#define AI_JUMPRANDOM_H

#include <SFML/Graphics.hpp>
#include "AI.hpp"

class Enemy;

class AI_JumpRandom : public AI
{
  
public:
  AI_JumpRandom(Enemy* enemy, const TileMap& tilemap);
  virtual void move();

private:
	bool _directionX;
	sf::Clock _clock;
};

#endif
#ifndef AI_LANDBASE_H
#define AI_LANDBASE_H

#include "AI.hpp"

class Enemy;

class AI_LandBase : public AI
{
  
public:
  AI_LandBase(Enemy* enemy);
  virtual void move();
};

#endif
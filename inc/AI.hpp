#ifndef AI_H
#define AI_H

class Enemy;
class AI
{
  
public:
  AI(Enemy *enemy);
  virtual void move() = 0;

protected:
	Enemy* _enemy; /** Ennemi qui utilise l'AI */
};

#endif
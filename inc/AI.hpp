#ifndef AI_H
#define AI_H

class Enemy;
class TileMap;
class AI
{
  
public:
  AI(Enemy* enemy, const TileMap& tilemap);
  virtual ~AI();
  virtual void move() = 0;

protected:
	Enemy* _enemy; /** Ennemi qui utilise l'AI */
	const TileMap& _tileMap;
};

#endif
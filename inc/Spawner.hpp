class Enemy;

class Spawner
{
public:
  Spawner(Enemy* prototype);
  Enemy* spawnEnemy();

private:
  Enemy* prototype_;
};
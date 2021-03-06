#include "Enemy.hpp"
#include "Boomer.hpp"
#include "AI_Boomer.hpp"
#include "Spawner.hpp"
#include "TileMap.hpp"
#include "Jumper.hpp"

Boomer::Boomer(const sf::Vector2f &taille, TileMap& tilemap, int fatPerFrame, Enemy* prototype) : Enemy(taille, tilemap), _fatPerFrame(fatPerFrame)
{
	_AI = new AI_Boomer(this, tilemap);
	_prototype = prototype;
    _jumperSpawn = new Spawner(_prototype);
   	_texture.loadFromFile("creeper.png");
	_shape.setTexture(&_texture, true);
}

Boomer::~Boomer()
{
	delete _jumperSpawn;
}

Enemy* Boomer::clone()
{
	return new Boomer(_shape.getSize(), _tileMap, _fatPerFrame, _prototype);
}

unsigned int Boomer::getFatPerFrame() const
{
	return _fatPerFrame;
}

bool Boomer::jumpOn()
{
	//Quand le boomer se fait sauter dessus, il faut spawn 6 minis jumpers qui partent chacuns dans une direction différente.
	_isDead = true;
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -2, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -1, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, -0, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, 1, 5));
	_tileMap.addEnemy(new Jumper(sf::Vector2f(8,8),sf::Vector2f(getPosition().x, getPosition().y + 5),_tileMap, 2, 5));
	return false;
}

#include <iostream>
#include "AI_LandBase.hpp"
#include "TileMap.hpp"
#include "Enemy.hpp"

AI_LandBase::AI_LandBase(Enemy* enemy, const TileMap& tilemap) : AI(enemy,tilemap)
{
	_directionX = false;
}

void AI_LandBase::move()
{
	 //On applique d'abord la gravité
    _enemy->addMouvement(_tileMap.getGravity());

    //On applique le futur mouvement
    if(_directionX)
    	_enemy->addMouvement(1,0);
    else
    	_enemy->addMouvement(-1,0);

    bool colGauche, colDroite, colBas;

    colGauche = _tileMap.collisionGauche(*_enemy);
    colDroite = _tileMap.collisionDroite(*_enemy);
    colBas = _tileMap.collisionBas(*_enemy);

    //Je change de sens si je detecte une collision
    if(colGauche || colDroite)
        _directionX = !_directionX;

    if(colBas)
    _enemy->setMouvement(sf::Vector2f(_enemy->getMouvement().x,0));
    	

    if(!(colDroite && colGauche))
        _enemy->setPosition(_enemy->getPosition().x + _enemy->getMouvement().x, _enemy->getPosition().y + _enemy->getMouvement().y); 

    _enemy->setMouvement(sf::Vector2f(0,_enemy->getMouvement().y));

}
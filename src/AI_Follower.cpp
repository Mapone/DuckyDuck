#include <iostream>
#include "AI_Follower.hpp"
#include "TileMap.hpp"
#include "Follower.hpp"
#include "Personnage.hpp"

AI_Follower::AI_Follower(Follower* follower, const TileMap& tilemap, const Personnage& p) : AI(follower,tilemap), _follower(follower), _perso(p)
{
	_directionX = false;
}

void AI_Follower::move()
{
	 //On applique d'abord la gravité
    _follower->addMouvement(_tileMap.getGravity());

    //On applique le futur mouvement
    if(_perso.getPosition().x > _follower->getPosition().x)
    	_follower->addMouvement(_follower->getSpeed(),0);
    else
    	_follower->addMouvement(-_follower->getSpeed(),0);

    bool colGauche, colDroite, colBas, colHaut;

    colGauche = _tileMap.collisionGauche(*_follower);
    colDroite = _tileMap.collisionDroite(*_follower);
    colBas = _tileMap.collisionBas(*_follower);

    if(colBas)
    _follower->setMouvement(sf::Vector2f(_follower->getMouvement().x,0));

    //Je change de sens si je detecte une collision
    if(colGauche || colDroite)
        _follower->setMouvement(sf::Vector2f(0,_follower->getMouvement().y));
    
    if(colBas && (colGauche || colDroite))
        _follower->addMouvement(sf::Vector2f(0,-_follower->getJumpHeight()));
        
    colHaut = _tileMap.collisionHaut(*_follower);
    if(colHaut)
        _follower->setMouvement(sf::Vector2f(_follower->getMouvement().x,0));

    if(!(colDroite && colGauche))
        _follower->setPosition(_follower->getPosition().x + _follower->getMouvement().x, _follower->getPosition().y + _follower->getMouvement().y); 

    //On reset le mouvement en x
    _follower->setMouvement(sf::Vector2f(0,_follower->getMouvement().y));

}
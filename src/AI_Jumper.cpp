#include <iostream>
#include "AI_Jumper.hpp"
#include "TileMap.hpp"
#include "Jumper.hpp"

AI_Jumper::AI_Jumper(Jumper* jumper, const TileMap& tilemap) : AI(jumper,tilemap), _jumper(jumper)
{
	_directionX = false;
}

void AI_Jumper::move()
{
	 //On applique d'abord la gravité
    _jumper->addMouvement(_tileMap.getGravity());

    //On applique le futur mouvement
    if(_directionX)
    	_jumper->addMouvement(_jumper->getSpeed(),0);
    else
    	_jumper->addMouvement(-_jumper->getSpeed(),0);

    bool colGauche, colDroite, colBas, colHaut;

    colGauche = _tileMap.collisionGauche(*_jumper);
    colDroite = _tileMap.collisionDroite(*_jumper);
    colBas = _tileMap.collisionBas(*_jumper);
    colHaut = _tileMap.collisionHaut(*_jumper);

    //Je change de sens si je detecte une collision
    if(colGauche || colDroite)
    {
        _directionX = !_directionX;
        _jumper->setMouvement(sf::Vector2f(0,_jumper->getMouvement().y));
        
    }
    //Le jumper saute si il detecte une collision en bas (ou en "haut" si la gravité est inversée)
    //Si grav negative, on inverse colBas et colHaut
    bool gravPosi = _tileMap.getGravity().y >= 0;
    if(!gravPosi)
    {
        if(colBas)
            _jumper->setMouvement(sf::Vector2f(_jumper->getMouvement().x,0));

        if(colHaut)
            _jumper->setMouvement(sf::Vector2f(_jumper->getMouvement().x,_jumper->getJumpHeight()));
    }
    else
    {
        if(colBas)
            _jumper->setMouvement(sf::Vector2f(_jumper->getMouvement().x,-_jumper->getJumpHeight()));

        if(colHaut)
            _jumper->setMouvement(sf::Vector2f(_jumper->getMouvement().x,0));
    }
    	

    if(!(colDroite && colGauche))
        _jumper->setPosition(_jumper->getPosition().x + _jumper->getMouvement().x, _jumper->getPosition().y + _jumper->getMouvement().y); 

    _jumper->setMouvement(sf::Vector2f(0,_jumper->getMouvement().y));

}
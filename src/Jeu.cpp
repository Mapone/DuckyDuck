#include <iostream>
#include <vector>
#include "Personnage.hpp"
#include "TileMap.hpp"
#include "Jeu.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "StateLevel.hpp"

using namespace std;

Jeu::Jeu(TileMap &t, Personnage &p):
_perso(p)
{
    TileMap *ptr = &t; 
	_levels.push_back(ptr);
	_currentLevel = 0;
    isOpen =true;

	//Initialisation de la Police
    if (!_font.loadFromFile("gamefont.ttf"))
        cerr << "#ERROR: Erreur lors du chargement de la police \"gamefont.tff\" " << endl;

	//Initialisation des Etats
    _stateMainMenu = new StateMainMenu(this);
    _stateLevel = new StateLevel(this, t, p);
	_currentState = _stateMainMenu;

}

Jeu::~Jeu()
{
	//delete pointeurs
}

bool Jeu::update()
{
    processInput();
    return isOpen;
}

void Jeu::addLevel(TileMap t)
{
	_levels.push_back(&t);
}

TileMap* Jeu::getCurrentLevel() const
{
    //TileMap* ptr = &_levels[_currentLevel];
	return _levels[_currentLevel];
}

const sf::Font& Jeu::getFont() const
{
	return _font;
}

void Jeu::setState(State* s)
{
    _currentState = s;
    s->init();
}

StateLevel* Jeu::getStateLevel() const
{
    return _stateLevel;
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    target.draw(*_currentState);
}

void Jeu::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        _currentState->pressSpace();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        _currentState->pressUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _currentState->pressDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _currentState->pressRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        _currentState->pressLeft();
    }
}
void Jeu::checkCollision()
{
    //On cherche d'ou viens la collision
    if(_levels[_currentLevel]->collisionBas(_perso.getShape(), _perso.getMouvement()) ||
       _levels[_currentLevel]->collisionHaut(_perso.getShape(), _perso.getMouvement()))
    {
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));
    }

    if(_levels[_currentLevel]->collisionDroite(_perso.getShape(),_perso.getMouvement()) ||
       _levels[_currentLevel]->collisionGauche(_perso.getShape(),_perso.getMouvement()))
    {

        _perso.setMouvement(sf::Vector2f(0,_perso.getMouvement().y));
    }

    //Si pas de colision en bas, on applique la gravité
    if(!_levels[_currentLevel]->collisionBas(_perso.getShape(), sf::Vector2f(_perso.getMouvement().x,1)))
    {        
        _perso.addMouvement(_levels[_currentLevel]->getGravity());
    }
    _perso.move();
}

void Jeu::close()
{
    isOpen = false;
}
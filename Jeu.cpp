#include <iostream>
#include <vector>
#include "Personnage.hpp"
#include "TileMap.hpp"
#include "Jeu.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"

using namespace std;

Jeu::Jeu(TileMap &t, Personnage &p):
_heros(p)
{
    TileMap *ptr = &t; 
	_levels.push_back(ptr);
	_currentLevel = 0;

	//Initialisation de la Police
    if (!_font.loadFromFile("gamefont.ttf"))
        cout << "#ERROR: Erreur lors du chargement de la police \"gamefont.tff\" " << endl;

	//Initialisation des Etats
    _stateMainMenu = new StateMainMenu(this);
	//_statePauseGame = new StateMenu(this);
	_currentState = _stateMainMenu;

}

Jeu::~Jeu()
{
	//delete pointeurs
}

void Jeu::update()
{
    processInput();
    checkCollision();
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

Personnage Jeu::getHero() const
{
    return _heros;
}

void Jeu::setState(State* s)
{
    _currentState = s;
}

StateLevel* Jeu::getStateLevel() const
{
    return _stateLevel;
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    //On draw l'etat actuel
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        _currentState->pressRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _currentState->pressLeft();
    }
}
void Jeu::checkCollision()
{
    //COLISIONS
    //On cherche d'ou viens la collision
    if(_levels[_currentLevel]->collisionBas(_heros.getPerso(), _heros.getMouvement()) ||
       _levels[_currentLevel]->collisionHaut(_heros.getPerso(), _heros.getMouvement()))
    {
        _heros.setMouvement(sf::Vector2f(_heros.getMouvement().x,0));
    }

    if(_levels[_currentLevel]->collisionDroite(_heros.getPerso(),_heros.getMouvement()) ||
       _levels[_currentLevel]->collisionGauche(_heros.getPerso(),_heros.getMouvement()))
    {

        _heros.setMouvement(sf::Vector2f(0,_heros.getMouvement().y));
    }

    //Si pas de colision en bas, on applique la gravité
    if(!_levels[_currentLevel]->collisionBas(_heros.getPerso(), sf::Vector2f(_heros.getMouvement().x,1)))
    {        
        _heros.addMouvement(_levels[_currentLevel]->getGravity());
    }
    _heros.move();
}
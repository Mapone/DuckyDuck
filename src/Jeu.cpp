#include <iostream>
#include <vector>
#include "Personnage.hpp"
#include "TileMap.hpp"
#include "Jeu.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "StateEscMenu.hpp"
#include "StateLevel.hpp"
#include "StateStats.hpp"

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
    _stateEscMenu = new StateEscMenu(this);
    _stateStats = new StateStats(this);
    _stateLevel = new StateLevel(this, t, p);
	_currentState = _stateMainMenu;

}

Jeu::~Jeu() {}

bool Jeu::update(sf::RenderWindow& window)
{
    processInput(window);
    return isOpen;
}

void Jeu::addLevel(TileMap* t)
{
	_levels.push_back(t);
}

TileMap* Jeu::getCurrentLevel() const
{
	return _levels[_currentLevel];
}

const sf::Font& Jeu::getFont() const
{
	return _font;
}

void Jeu::setState(State* s)
{
    _currentState = s;
}

void Jeu::initStateLevel() const
{
    _stateLevel->init();
}

bool Jeu::changeToNextLevel()
{
    if(++_currentLevel < _levels.size())
    {
        ++_currentLevel;
        _stateLevel->setLevel(*getCurrentLevel());
        return true;
    }
    return false;
}


StateLevel* Jeu::getStateLevel() const
{
    return _stateLevel;
}

StateEscMenu* Jeu::getStateEscMenu() const
{
    return _stateEscMenu;
}

StateStats* Jeu::getStateStats() const
{
    return _stateStats;
}

StateMainMenu* Jeu::getStateMainMenu() const
{
    return _stateMainMenu;
}



void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    target.draw(*_currentState);
}

void Jeu::processInput(sf::RenderWindow& window)
{
    sf::Event event;
    // tant qu'il y a des évènements à traiter...
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _currentState->pressEsc();        
            }
        } 
    }
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

void Jeu::close()
{
    isOpen = false;
}
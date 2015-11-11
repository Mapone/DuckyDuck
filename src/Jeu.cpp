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
using namespace sf;

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
    _stateStats = new StateStats(this,p);
    _stateLevel = new StateLevel(this, &t, p);
	_currentState = _stateMainMenu;

}

Jeu::~Jeu() {}

void Jeu::start()
{

    //----------------------Fenetre----------------------
    //---------------------------------------------------
    const unsigned int LARGEUR_FENETRE = 800;
    const unsigned int HAUTEUR_FENETRE = 448;


    ContextSettings settings;
    settings.antialiasingLevel = 8;
    //Ouverture de la fenêtre principale
    RenderWindow window(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "DuckyDuck",Style::Default, settings);
    //Limite de fps
    window.setFramerateLimit(60);

    //-------------------Boucle principale----------------
    //----------------------------------------------------

    bool pressEsc = true;
    bool pressEnter = true;

    while (window.isOpen() && isOpen)
    {
        Event event;
        while (window.pollEvent(event))
        {       
            //Si on ferme la fenêtre par n'importe quel moyen (croix, ALT+F4...)
            if (event.type == Event::Closed)
                window.close();

            //On regarde si une touche a été pressée
            if (event.type == sf::Event::KeyPressed)
            {
                //On veut que l'action de la touche ne soit affectué que pour la toute première pression de celle-ci
                //Si c'est le cas, on met sur false un booléen qui sera inchangé tant que la touche n'aura pas été relachée
                if (event.key.code == sf::Keyboard::Escape && pressEsc)
                {
                    _currentState->pressEsc();
                    pressEsc = false;
                }
                if (event.key.code == sf::Keyboard::Return && pressEnter)
                {
                    _currentState->pressEnter();
                    pressEnter = false;
                }
            }
            //La touche est relaché, on change donc le booléen
            if(event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    pressEsc = true;
                if (event.key.code == sf::Keyboard::Return)
                    pressEnter = true;      
            }
        }
        window.clear(sf::Color::Black);
        _currentState->update();
        input();
        window.draw(*this);
        window.display();
    }
    window.close();
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
    if(_currentLevel+1 < _levels.size())
    {
        ++_currentLevel;
        _stateLevel->setLevel(getCurrentLevel());
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

StateStats* Jeu::getStateStats(bool IsLevelFinished) const
{
    _stateStats->setIsLevelFinished(IsLevelFinished);
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

void Jeu::input()
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

void Jeu::close()
{
    isOpen = false;
}

void Jeu::restartCharClock() const
{
    _perso.restartClock();
}

TileMap* Jeu::resetLevel()
{
    string name = _levels[_currentLevel]->getLevelName();
    sf::Vector2f grav = _levels[_currentLevel]->getGravity();
    _levels[_currentLevel] = new TileMap(name, grav);
    return _levels[_currentLevel];
}

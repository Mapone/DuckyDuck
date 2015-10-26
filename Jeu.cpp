
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Personnage.hpp"
#include "TileMap.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "Jeu.hpp"

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
	//_stateMainMenu = new StateMainMenu(this);
	//_actualState = _stateMainMenu;

}

Jeu::~Jeu()
{
	//delete pointeurs
}

void Jeu::addLevel(TileMap t)
{
	_levels.push_back(&t);
}

TileMap* Jeu::getCurrentLevel()
{
    //TileMap* ptr = &_levels[_currentLevel];
	return _levels[_currentLevel];
}

sf::Font& Jeu::getFont()
{
	return _font;
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    target.draw(*_levels[_currentLevel]);
    //sf::RectangleShape r(sf::Vector2f(2,2));
    target.draw(_heros.getPerso());


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        if(_levels[_currentLevel]->collisionBas(_heros.getPerso(),sf::Vector2f(_heros.getMouvement().x,1)))
        _heros.addMouvement(sf::Vector2f(0,-20));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        _heros.addMouvement(sf::Vector2f(-0.2,0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _heros.addMouvement(sf::Vector2f(0.2,0));
    }

    cout << "MvtB " << _heros.getMouvement().x <<":"<< _heros.getMouvement().y << endl;

    //On cherche d'ou viens la collision
    if(_levels[_currentLevel]->collisionBas(_heros.getPerso(), _heros.getMouvement()) ||
       _levels[_currentLevel]->collisionHaut(_heros.getPerso(), _heros.getMouvement()))
    {

        if(_levels[_currentLevel]->collisionBas(_heros.getPerso(), _heros.getMouvement()))
            cout <<"ColisionBas"<<endl;
        if(_levels[_currentLevel]->collisionHaut(_heros.getPerso(), _heros.getMouvement()))
            cout <<"ColisionHaut"<<endl;

        _heros.setMouvement(sf::Vector2f(_heros.getMouvement().x,0));
    }

    if(_levels[_currentLevel]->collisionDroite(_heros.getPerso(),_heros.getMouvement()) ||
       _levels[_currentLevel]->collisionGauche(_heros.getPerso(),_heros.getMouvement()))
    {
        if(_levels[_currentLevel]->collisionDroite(_heros.getPerso(), _heros.getMouvement()))
            cout <<"ColisionDroite"<<endl;
        if(_levels[_currentLevel]->collisionGauche(_heros.getPerso(), _heros.getMouvement()))
            cout <<"ColisionGauche"<<endl;

        _heros.setMouvement(sf::Vector2f(0,_heros.getMouvement().y));
    }

    cout << "MvtA " << _heros.getMouvement().x <<":"<< _heros.getMouvement().y << endl;
    cout << "PosH " << _heros.getPerso().getPosition().x <<":"<< _heros.getPerso().getPosition().y << endl;

    //Si pas de colision en bas, on applique la gravité
    if(!_levels[_currentLevel]->collisionBas(_heros.getPerso(), sf::Vector2f(_heros.getMouvement().x,1)))
    {        
        _heros.addMouvement(_levels[_currentLevel]->getGravity());
        cout << "gravité" << endl;
    }

    _heros.move();
}
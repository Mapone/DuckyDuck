#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"


StateMainMenu::StateMainMenu(Jeu *jeu) : State(jeu)
{
    _current = 0;

	sf::Text gameName;
    gameName.setFont(jeu->getFont());
    gameName.setString("DuckyDuck");
    gameName.setCharacterSize(20);
    gameName.setColor(sf::Color::Green);
    gameName.setPosition(300,100);
    _gameName = _gameName;

    sf::Text Jouer;
    Jouer.setFont(jeu->getFont());
    Jouer.setString("Jouer");
    Jouer.setCharacterSize(18);
    Jouer.setColor(sf::Color::Green);
    Jouer.setPosition(350,200);
    _Jouer = Jouer;

   	sf::Text Quitter;
    Quitter.setFont(jeu->getFont());
    Quitter.setString("Quitter");
    Quitter.setCharacterSize(18);
    Quitter.setColor(sf::Color::Green);
    Quitter.setPosition(400,250);
    _Quitter = Quitter;

    sf::CircleShape triangle(10, 3);
    triangle.setRotation(90);
    triangle.setFillColor(sf::Color::Red);
    triangle.setPosition(330,200);
    _triangle = triangle;
}
StateMainMenu::~StateMainMenu(){}

void StateMainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
	target.draw(_triangle);
	target.draw(_gameName);
	target.draw(_Jouer);
	target.draw(_Quitter);
}
void StateMainMenu::pressUp()
{
    if( _current != 0)
        --_current;
}
void StateMainMenu::pressDown()
{
    if( _current == 0)
        ++_current;
}
void StateMainMenu::pressSpace()
{
    State *s = _jeu->getStateLevel();
    
    if(_current == 0)
        _jeu->setState(_jeu->getStateLevel());
    else
        _jeu->close();
}

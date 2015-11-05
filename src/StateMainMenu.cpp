#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Jeu.hpp"
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "StateLevel.hpp"


StateMainMenu::StateMainMenu(Jeu *jeu) : State(jeu)
{
    _current = 0;

	sf::Text gameName;
    gameName.setFont(jeu->getFont());
    gameName.setString("DuckyDuck");
    gameName.setCharacterSize(20);
    gameName.setColor(sf::Color::White);
    gameName.setPosition(300,100);
    _gameName = gameName;

    sf::Text Jouer;
    Jouer.setFont(jeu->getFont());
    Jouer.setString("Jouer");
    Jouer.setCharacterSize(18);
    Jouer.setColor(sf::Color::White);
    Jouer.setPosition(350,200);
    _Jouer = Jouer;

   	sf::Text Quitter;
    Quitter.setFont(jeu->getFont());
    Quitter.setString("Quitter");
    Quitter.setCharacterSize(18);
    Quitter.setColor(sf::Color::White);
    Quitter.setPosition(350,250);
    _Quitter = Quitter;

    sf::CircleShape triangle(10, 3);
    triangle.setRotation(90);
    triangle.setFillColor(sf::Color::White);
    triangle.setPosition(330,200);
    _triangle = triangle;
}
StateMainMenu::~StateMainMenu(){}

void StateMainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
	target.draw(_gameName);
    target.draw(_triangle);
	target.draw(_Jouer);
	target.draw(_Quitter);
}
void StateMainMenu::pressUp()
{
    if( _current != 0)
    {   
        --_current;
        _triangle.setPosition(330,200);    
    }
}
void StateMainMenu::pressDown()
{
    if( _current == 0)
    {   
        ++_current;
        _triangle.setPosition(330,250);    
    }
}
void StateMainMenu::pressEnter()
{
    if(_current == 0)
    {
        _jeu->restartCharClock();
        _jeu->initStateLevel();
        _jeu->setState(_jeu->getStateLevel());
    }
    else
        _jeu->close();
}
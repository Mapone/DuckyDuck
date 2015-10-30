#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Jeu.hpp"
#include "State.hpp"
#include "StateEscMenu.hpp"
#include "StateLevel.hpp"


StateEscMenu::StateEscMenu(Jeu *jeu) : State(jeu)
{
    _current = 0;

  sf::Text gameName;
    gameName.setFont(jeu->getFont());
    gameName.setString("DuckyDuck - Pause");
    gameName.setCharacterSize(20);
    gameName.setColor(sf::Color::White);
    gameName.setPosition(300,100);
    _gameName = gameName;

    sf::Text Reprendre;
    Reprendre.setFont(jeu->getFont());
    Reprendre.setString("Reprendre");
    Reprendre.setCharacterSize(18);
    Reprendre.setColor(sf::Color::White);
    Reprendre.setPosition(350,200);
    _Reprendre = Reprendre;

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
StateEscMenu::~StateEscMenu(){}

void StateEscMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
  target.draw(_gameName);
  target.draw(_triangle);
  target.draw(_Reprendre);
  target.draw(_Quitter);
}
void StateEscMenu::pressUp()
{
    if( _current != 0)
    {   
        --_current;
        _triangle.setPosition(330,200);    
    }
}
void StateEscMenu::pressDown()
{
    if( _current == 0)
    {   
        ++_current;
        _triangle.setPosition(330,250);    
    }
}
void StateEscMenu::pressSpace()
{
    if(_current == 0)
        pressEsc();
    else
        _jeu->close();
}

void StateEscMenu::pressEsc()
{
    _jeu->setState(_jeu->getStateLevel());
}
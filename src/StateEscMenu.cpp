#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Jeu.hpp"
#include "State.hpp"
#include "StateEscMenu.hpp"
#include "StateLevel.hpp"

const int nbChoice = 2; /** Nombre de choix 0-nb*/

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

    sf::Text Recommencer;
    Recommencer.setFont(jeu->getFont());
    Recommencer.setString("Recommencer");
    Recommencer.setCharacterSize(18);
    Recommencer.setColor(sf::Color::White);
    Recommencer.setPosition(350,250);
    _Recommencer = Recommencer;

    sf::Text Quitter;
    Quitter.setFont(jeu->getFont());
    Quitter.setString("Quitter");
    Quitter.setCharacterSize(18);
    Quitter.setColor(sf::Color::White);
    Quitter.setPosition(350,300);
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
  target.draw(_Recommencer);
  target.draw(_Quitter);
}
void StateEscMenu::pressUp()
{
    if( _current > 0)
    {   
        --_current;
        _triangle.setPosition(330,200+_current*50);
    }
    else
    {
        _current = nbChoice;
        _triangle.setPosition(330,200+_current*50);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void StateEscMenu::pressDown()
{
    if( _current < nbChoice)
    {   
        ++_current;
        _triangle.setPosition(330,200+_current*50);
    }
    else
    {
        _current = 0;
        _triangle.setPosition(330,200+_current*50);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void StateEscMenu::pressEnter()
{
    switch(_current)
    {
        case 0:
            pressEsc();
            break;

        case 1:
            _jeu->getStateLevel()->setLevel(_jeu->resetLevel());
            _jeu->initStateLevel();
            pressEsc();
            break;
        
        case 2:
            _jeu->close();
            break;

        default:
            std::cerr << "#ERROR 42" << std::endl;
            break;
    }
}

void StateEscMenu::pressEsc()
{
    _jeu->setState(_jeu->getStateLevel());
}
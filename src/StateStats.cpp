#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Jeu.hpp"
#include "State.hpp"
#include "StateStats.hpp"
#include "StateLevel.hpp"
#include "StateMainMenu.hpp"


StateStats::StateStats(Jeu *jeu) : State(jeu)
{
    _levelName.setFont(jeu->getFont());
    _levelName.setString("DuckyDuck");
    _levelName.setCharacterSize(20);
    _levelName.setColor(sf::Color::White);
    _levelName.setPosition(300,100);

    _scoreTxt.setFont(jeu->getFont());
    _scoreTxt.setString("_scoreTxt");
    _scoreTxt.setCharacterSize(18);
    _scoreTxt.setColor(sf::Color::White);
    _scoreTxt.setPosition(350,200);

    _scoreNb.setFont(jeu->getFont());
    _scoreNb.setString("_scoreNb");
    _scoreNb.setCharacterSize(18);
    _scoreNb.setColor(sf::Color::White);
    _scoreNb.setPosition(350,200);

    _enemyTxt.setFont(jeu->getFont());
    _enemyTxt.setString("_enemyTxt");
    _enemyTxt.setCharacterSize(18);
    _enemyTxt.setColor(sf::Color::White);
    _enemyTxt.setPosition(350,200);

    _enemyNb.setFont(jeu->getFont());
    _enemyNb.setString("_enemyNb");
    _enemyNb.setCharacterSize(18);
    _enemyNb.setColor(sf::Color::White);
    _enemyNb.setPosition(350,200);

    _timeTxt.setFont(jeu->getFont());
    _timeTxt.setString("_timeTxt");
    _timeTxt.setCharacterSize(18);
    _timeTxt.setColor(sf::Color::White);
    _timeTxt.setPosition(350,200);

    _timeNb.setFont(jeu->getFont());
    _timeNb.setString("_timeNb");
    _timeNb.setCharacterSize(18);
    _timeNb.setColor(sf::Color::White);
    _timeNb.setPosition(350,200);

    _pressSpace.setFont(jeu->getFont());
    _pressSpace.setString("_pressSpace");
    _pressSpace.setCharacterSize(18);
    _pressSpace.setColor(sf::Color::White);
    _pressSpace.setPosition(350,200);
}
StateStats::~StateStats(){}

void StateStats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
	target.draw(_levelName);
    target.draw(_scoreTxt);
	target.draw(_enemyTxt);
	target.draw(_enemyNb);
    target.draw(_timeTxt);
    target.draw(_timeNb);
    target.draw(_pressSpace);
}
void StateStats::pressUp(){}
void StateStats::pressDown(){}
void StateStats::pressSpace()
{
    using namespace std;
    //On regarde si il existe un niveau suivant
    if(_jeu->changeToNextLevel())
    {
        _jeu->initStateLevel();
        _jeu->setState(_jeu->getStateLevel());
    }
    else
        _jeu->setState(_jeu->getStateMainMenu());
}
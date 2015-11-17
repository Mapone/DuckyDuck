#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Jeu.hpp"
#include "State.hpp"
#include "StateStats.hpp"
#include "StateLevel.hpp"
#include "StateMainMenu.hpp"

StateStats::StateStats(Jeu *jeu, Personnage& p) : State(jeu), _perso(p)
{
    _isLevelFinished = true;
 
    _levelName.setFont(_jeu->getFont());
    _levelName.setString("");
    _levelName.setCharacterSize(20);
    _levelName.setColor(sf::Color::White);

    _scoreTxt.setFont(_jeu->getFont());
    _scoreTxt.setString("Score");
    _scoreTxt.setCharacterSize(18);
    _scoreTxt.setColor(sf::Color::White);
    _scoreTxt.setPosition(100,200);

    _scoreNb.setFont(_jeu->getFont());
    _scoreNb.setString("_scoreNb");
    _scoreNb.setCharacterSize(18);
    _scoreNb.setColor(sf::Color::White);
    _scoreNb.setPosition(500,200);

    _enemyTxt.setFont(_jeu->getFont());
    _enemyTxt.setString("Ennemis morts");
    _enemyTxt.setCharacterSize(18);
    _enemyTxt.setColor(sf::Color::White);
    _enemyTxt.setPosition(100,250);

    _enemyNb.setFont(_jeu->getFont());
    _enemyNb.setString("_enemyNb");
    _enemyNb.setCharacterSize(18);
    _enemyNb.setColor(sf::Color::White);
    _enemyNb.setPosition(500,250);

    _timeTxt.setFont(_jeu->getFont());
    _timeTxt.setString("Temps");
    _timeTxt.setCharacterSize(18);
    _timeTxt.setColor(sf::Color::White);
    _timeTxt.setPosition(100,300);

    _timeNb.setFont(_jeu->getFont());
    _timeNb.setString("_timeNb");
    _timeNb.setCharacterSize(18);
    _timeNb.setColor(sf::Color::White);
    _timeNb.setPosition(500,300);


    std::string pStxt = "Appuyer sur Entrer pour continuer";
    int posX = 400 - ((pStxt.size() * 18)/2);  
    _pressSpace.setFont(_jeu->getFont());
    _pressSpace.setString(pStxt);
    _pressSpace.setCharacterSize(18);
    _pressSpace.setColor(sf::Color::White);
    _pressSpace.setPosition(posX,400);
}

StateStats::~StateStats(){}

void StateStats::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(_levelName);
    target.draw(_scoreTxt);
    target.draw(_scoreNb);
    target.draw(_enemyTxt);
    target.draw(_enemyNb);
    target.draw(_timeTxt);
    target.draw(_timeNb);
    target.draw(_pressSpace);
}
void StateStats::pressUp(){}
void StateStats::pressDown(){}
void StateStats::pressEnter()
{
    _perso.restartClock();

    if(_isLevelFinished)
    {
        //On regarde si il existe un niveau suivant
        if(_jeu->changeToNextLevel())
        {
            _jeu->initStateLevel();
            _jeu->setState(_jeu->getStateLevel());
        }
        else
            _jeu->setState(_jeu->getStateMainMenu());
    }
    else
    {
        _jeu->initStateLevel();
        _jeu->setState(_jeu->getStateLevel());
    }
}

void StateStats::setIsLevelFinished(bool IsLevelFinished)
{
    _isLevelFinished = IsLevelFinished;
    init();
}

void StateStats::init()
{
    //On Ecrit le texte suivant la situiation
    if(_isLevelFinished)
        _levelName.setString("Niveau Fini: " + _jeu->getCurrentLevel()->getLevelName());
    else
        _levelName.setString("GAME OVER !");

    //On determine ensuite la position du texte
    int posX = 400 - ((_levelName.getString().toAnsiString().size() * 20)/2); 
    _levelName.setPosition(posX,100);

    _perso.setCurrentScore(10*_perso.getCurrentKill()-(int)_perso.getElapsedTime().asSeconds());
    _scoreNb.setString(std::to_string((int)_perso.getCurrentScore()));
    _perso.setTotalScore(_perso.getTotalScore()+_perso.getCurrentScore());
    _enemyNb.setString(std::to_string((int)_perso.getCurrentKill()));
    _timeNb.setString(std::to_string((int)_perso.getElapsedTime().asSeconds()));
}
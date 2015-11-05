#ifndef STATESTATS_H
#define STATESTATS_H


#include <SFML/Graphics.hpp>
#include "State.hpp"

class TileMap;

class StateStats : public State
{
public:
  StateStats(Jeu *jeu);
  ~StateStats();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void pressUp();
  virtual void pressDown();
  virtual void pressEnter();
  void setIsLevelFinished(bool IsLevelFinished);

private:
	sf::Text _levelName;
  sf::Text _scoreTxt;
	sf::Text _scoreNb;
  sf::Text _enemyTxt;
  sf::Text _enemyNb;
  sf::Text _timeTxt;
  sf::Text _timeNb;
	sf::Text _pressSpace;
  bool _isLevelFinished;
};

#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMenu.hpp"

StateMenu::StateMenu(Jeu *jeu, Bouton &b)
{
	State::State(jeu);
	_selected = 0;
	_listofChoices = new std::Vector(Boutons);
	_listofChoices.push_back(b);
}
StateMenu::~StateMenu()
{
	State::~State();
}
virtual void StateMenu::pressUp()
{
	_selected ? :_selected--;
}
virtual void StateMenu::pressDown()
{
	_selected == _listofChoices.size() -1 ? _selected++ : ;
}
virtual void StateMenu::pressSpace()
{
	_listofChoices[_selected].action();
}
virtual void StateMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_listofChoices[_selected].setColor(sf::Color::Green);
	for(unsigned int i = 0; i<_listofChoices.size();++i)
	{
		draw(_listofChoices[i]);
	}
}
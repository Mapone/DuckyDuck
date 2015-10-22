#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.hpp"


State::State(Jeu *jeu):_jeu(jeu){}
State::~State(){delete _jeu;}
void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//(void) est utilisé pour ne pas avoir le warning "unused parameter"
	(void)target;
	(void)states;
}
void State::pressUP(){}
void State::pressDown(){}
void State::pressLeff(){}
void State::pressRight(){}
void State::pressSpace(){}

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.hpp"


State::State(Jeu *jeu) : _jeu(jeu) {}
State::~State()
{
	delete _jeu;
}

void State::pressUp(){}
void State::init(){}
void State::pressDown(){}
void State::pressLeft(){}
void State::pressRight(){}
void State::pressSpace(){}
void State::pressEsc(){}
void State::pressEnter(){}
void State::update(){}


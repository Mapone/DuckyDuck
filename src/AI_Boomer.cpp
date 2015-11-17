#include <iostream>
#include "AI_Boomer.hpp"
#include "TileMap.hpp"
#include "Boomer.hpp"

AI_Boomer::AI_Boomer(Boomer* boomer, const TileMap& tilemap) : AI(boomer,tilemap), _boomer(boomer)
{
    _clock.restart();
}

void AI_Boomer::move()
{
    //Grossissement
    if(_clock.getElapsedTime().asSeconds() > 1 && _clock.getElapsedTime().asSeconds() < 2)
        _boomer->setSize(_boomer->getSize().x + _boomer->getFatPerFrame(),_boomer->getSize().y + _boomer->getFatPerFrame());

    if(_clock.getElapsedTime().asSeconds() > 3 && _clock.getElapsedTime().asSeconds() < 4)
        _boomer->setSize(_boomer->getSize().x - _boomer->getFatPerFrame(),_boomer->getSize().y - _boomer->getFatPerFrame());

    if(_clock.getElapsedTime().asSeconds() > 5)
        _clock.restart();
}
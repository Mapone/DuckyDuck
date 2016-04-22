/**************************************
DUCKYDUCK
**************************************/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"

using namespace std;

////////////////////////////////////
////////////INITIALISATION//////////
////////////////////////////////////

int main()
{
//-------------------Creation du personnage-----------------------
//----------------------------------------------------------------

    //On initialize une texture
    Personnage ducky(sf::Vector2f(15,15));


//-------------------Chargement du premier niveau-----------------
//----------------------------------------------------------------
    
    sf::Vector2f gravity(0,0.2);
    sf::Vector2f lowGravity(0,0.01);
    TileMap map("invertGrav", gravity, ducky);

//-------------------Création du Jeu------------------------------
//----------------------------------------------------------------

    Jeu jeu(map, ducky);

    
//--------- Création et ajout des niveaux -----------------
//---------------------------------------------------------
    TileMap map0("Level",gravity, ducky);
    jeu.addLevel(&map0);
    TileMap map1("prairie", gravity, ducky);
    jeu.addLevel(&map1);
    TileMap map2("lowGrav", lowGravity, ducky);
    jeu.addLevel(&map2);
    TileMap map3("Cave", gravity, ducky);
    jeu.addLevel(&map3);
    TileMap map4("troll", gravity, ducky);
    jeu.addLevel(&map4);

///////////////////////////////////////
////////////LANCEMENT DU JEU//////////
/////////////////////////////////////

    jeu.start();

    return EXIT_SUCCESS;
}
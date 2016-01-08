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

    //On crée une image contenant la texture du personnage
    sf::Image i;
    if(!i.loadFromFile("Duck.png"))
    cerr << "#ERROR: Erreur lors du chargement d'image \"Duck.png\"" << endl;

    //On inverse l'image pour que le personnage regarde vers la droite
    i.flipHorizontally();

    //On initialize une texture
    sf::Texture t;
    Personnage ducky(sf::Vector2f(15,15), i, t);


//-------------------Chargement du premier niveau-----------------
//----------------------------------------------------------------
    
    sf::Vector2f gravity(0,0.2);
    sf::Vector2f lowGravity(0,0.01);
    TileMap map("first", gravity, ducky);

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

    return 0;
}
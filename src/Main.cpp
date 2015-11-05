/**************************************
JEU ALAKON
**************************************/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"

using namespace std;

//TODO
/*
Si y'a le temps:
    - Arret du programme si la map n'est pas valide (pas de spawn ou de fin)
    - Remplacer la touche entrée par espace dans les menus (chiant à faire)
    - Sortie de map


*/

////////////////////////////////////
////////////INITIALISATION//////////
////////////////////////////////////

int main()
{
//-------------------Chargement du premier niveau-----------------
//----------------------------------------------------------------
    
    sf::Vector2f gravity(0,0.2);
    TileMap map1("lvl4", gravity);

//-------------------Creation du personnage-----------------------
//----------------------------------------------------------------

    Personnage mario(sf::Vector2f(15,15));

//-------------------Création du Jeu------------------------------
//----------------------------------------------------------------

    Jeu jeu(map1, mario);

    
//--------- Création et ajout des niveaux -----------------
//---------------------------------------------------------
    TileMap map2("lvl3", gravity);
    jeu.addLevel(&map2);

///////////////////////////////////////
////////////LANCEMENT DU JEU//////////
/////////////////////////////////////

    jeu.start();

    return 0;
}
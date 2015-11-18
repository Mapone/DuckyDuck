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

*/

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
    TileMap map("lvl4", gravity, ducky);

//-------------------Création du Jeu------------------------------
//----------------------------------------------------------------

    Jeu jeu(map, ducky);

    
//--------- Création et ajout des niveaux -----------------
//---------------------------------------------------------
    TileMap map1("montagne", gravity, ducky);
    jeu.addLevel(&map1);
    TileMap map2("lvl3", gravity, ducky);
    jeu.addLevel(&map2);

///////////////////////////////////////
////////////LANCEMENT DU JEU//////////
/////////////////////////////////////

    jeu.start();

    return 0;
}
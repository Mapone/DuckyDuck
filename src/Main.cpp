/**************************************
JEU ALAKON
**************************************/

#include <iostream>
#include <string> //to_String
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Personnage.hpp"
#include "Jeu.hpp"

using namespace std;
using namespace sf;



int main()
{
////////////////////////////////////
////////////INITIALISATION//////////
////////////////////////////////////

const int LARGEUR_FENETRE = 800;
const int HAUTEUR_FENETRE = 448;

	
//----------------------Fenetre----------------------
//----------------------------------------------------
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Ouverture de la fenêtre principale
    RenderWindow window(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "DuckyDuck",Style::Default, settings);
    //Limite de fps
    window.setFramerateLimit(60);


//-------------------Chargement du premier niveau-----------------
//----------------------------------------------------------------
    
    Vector2f gravity(0,0.2);
    TileMap map("lvl3.bmp", gravity);

//-------------------Creation du personnage-----------------------
//----------------------------------------------------------------

    Personnage mario(Vector2f(10,10));
    mario.getShape().setPosition(32,64);

//-------------------Création du Jeu------------------------------
//----------------------------------------------------------------

    Jeu jeu(map, mario);

    
//--------- Création et ajout des niveaux -----------------
//---------------------------------------------------------



///////////////////////////////////////
////////////LANCEMENT DU JEU//////////
/////////////////////////////////////


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {       
            if (event.type == Event::Closed)
                window.close();
        }

   // std::cout << mario.getMouvement().x << ":" << mario.getMouvement().x << std::endl;
        window.clear(sf::Color::Black);
        if(!jeu.update())
            break;
        window.draw(jeu);
        window.display();
    }
    
    window.close();
    return 0;
}
/**************************************
JEU ALAKON
**************************************/

#include <iostream>
#include <string> //to_String
#include <stdlib.h> //rand
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

using namespace std;
using namespace sf;



int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////

    const int LARGEUR_FENETRE = 320;
    const int HAUTEUR_FENETRE = 240;

//----------------------Fenetre----------------------
//----------------------------------------------------
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Ouverture de la fenêtre principale
    RenderWindow window(VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "DuckyDuck",Style::Default, settings);
    //Limite à 60fps
    window.setFramerateLimit(60);

//----------------Police et textes -----------------------
//--------------------------------------------------------

    Font fontOldSchool;
    if (!fontOldSchool.loadFromFile("gamefont.ttf"))
        cout << "#ERROR: Erreur lors du chargement de la police \"gamefont.tff\" " << endl;


    Image niveau;
cout << "A" << endl;
    TileMap map(niveau);
    cout << "A" << endl;
    if (!map.load("tileset2.png", sf::Vector2u(16, 16), map.getLevel(), 20, 15))
        cout << "#ERROR: Erreur lors du chargement du tileset" << endl;


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {       
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(map);
        window.display();
    }
    return 0;
}
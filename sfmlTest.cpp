/**************************************
JEU ALAKON
**************************************/

#include <iostream>
#include <string> //to_String
#include <stdlib.h> //rand
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "Personnage.hpp"

using namespace std;
using namespace sf;



int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////

    const int LARGEUR_FENETRE = 800;
    const int HAUTEUR_FENETRE = 448;
	const int NB_DIVISION_BLOCS = 4;
    const int NB_TUILES = (LARGEUR_FENETRE*HAUTEUR_FENETRE*NB_DIVISION_BLOCS)/(16*16);

	
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

	
//--------- Creation du tableau de collisions -------------
//---------------------------------------------------------

    bool collisions[NB_TUILES*NB_DIVISION_BLOCS];
    Image niveau;
    TileMap map(niveau);
    if (!map.load("tileset2.png", sf::Vector2u(16, 16), map.getLevel(), 50, 28, collisions))
        cout << "#ERROR: Erreur lors du chargement du tileset" << endl;

    Personnage mario(Vector2f(16,16));
    mario.getPerso().setPosition(32,64);

    Vector2f gravity(0,0.05);

    bool tmp = true;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && tmp)
        {
            mario.addMouvement(Vector2f(0,-20));
            tmp = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            mario.addMouvement(Vector2f(-0.2,0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mario.addMouvement(Vector2f(0.2,0));
        }
        mario.addMouvement(gravity);
        mario.move();
        window.draw(mario.getPerso());
        window.display();
    }
    return 0;
}
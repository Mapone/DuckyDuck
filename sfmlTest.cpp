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

	
//--------- Chargement du niveau --------------------------
//---------------------------------------------------------

    String niveau = ("lvl3.bmp");
    TileMap map(niveau);

    if (!map.load("tileset2.png", sf::Vector2u(16, 16), map.getLevel()))
        cout << "#ERROR: Erreur lors du chargement du tileset" << endl;

    Personnage mario(Vector2f(10,10));
    mario.getPerso().setPosition(32,64);

    Vector2f gravity(0,0.2);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            mario.addMouvement(Vector2f(0,-20));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            mario.addMouvement(Vector2f(-0.2,0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mario.addMouvement(Vector2f(0.2,0));
        }

        // Si il n'y a pas de collision, on bouge le perso
        if(map.collision(mario.getPerso(), mario.getMouvement()))
        {
            mario.move();
        }            

        //Si pas de colision en bas, on applique la gravité
        if(map.collisionBas(mario.getPerso(), mario.getMouvement()))
            mario.addMouvement(gravity);


        if(!map.collision(mario.getPerso(), mario.getMouvement()))
            mario.setMouvement(Vector2f(mario.getMouvement().x,0));

        cout << mario.getMouvement().x <<":"<< mario.getMouvement().y << endl;

        window.draw(mario.getPerso());
        window.display();
    }
    return 0;
}
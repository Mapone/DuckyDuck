#include <iostream>
#include <string> //to_String
#include <stdlib.h> //rand
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////

    const int LARGEUR_FENETRE = 800;
    const int HAUTEUR_FENETRE = 800;
    const int TAILLE_HUD = 16;
    const int TAILLE_CARRE = 10;

//----------------------Fenetre----------------------
//----------------------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Ouverture de la fenêtre principale
    sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "DuckyDuck",sf::Style::Default, settings);
    //Limite à 60fps
    window.setFramerateLimit(60);

//----------------Police et textes -----------------------
//--------------------------------------------------------

    sf::Font fontOldSchool;
    if (!fontOldSchool.loadFromFile("gamefont.ttf"))
        cout << "#ERROR: Erreur lors du chargement de la police \"gamefont.tff\" " << endl;

    sf::Text staticScore;
    staticScore.setFont(fontOldSchool);
    staticScore.setString("Nombre de points:");
    staticScore.setCharacterSize(TAILLE_HUD);
    staticScore.setColor(sf::Color::White);
    staticScore.setPosition(400,0);

    sf::Text score;
    score.setFont(fontOldSchool);
    score.setString("0");
    score.setCharacterSize(16);
    score.setColor(sf::Color::White);
    score.setPosition(700,0);

    int randomX = rand() % (LARGEUR_FENETRE-TAILLE_CARRE);
    int randomY = rand() % (HAUTEUR_FENETRE-TAILLE_CARRE);

    sf::RectangleShape randomRect(sf::Vector2f(TAILLE_CARRE,TAILLE_CARRE));
    randomRect.setFillColor(sf::Color::Red);
    randomRect.setPosition(randomX,randomY);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {       
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int i_score  = stoi((string)score.getString(),NULL,10);
        ++i_score;
        score.setString(to_string(i_score));

        if(i_score%20==0)
        {
            randomX = rand() % (LARGEUR_FENETRE-TAILLE_CARRE);
            randomY = rand() % (HAUTEUR_FENETRE-TAILLE_CARRE)+TAILLE_HUD;
            randomRect.setPosition(randomX,randomY);
        }

        window.clear();
        window.draw(staticScore);
        window.draw(score);
        window.draw(randomRect);
        window.display();
    }

    return 0;
}
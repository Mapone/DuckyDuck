/**************************************
JEU ALAKON
**************************************/

#include <iostream>
#include <string> //to_String
#include <stdlib.h> //rand
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

void updateScore(int i, Text &score)
{
    int i_score  = stoi((string)score.getString(),NULL,10);
    ++i_score;
    score.setString(to_string(i_score));
}

int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////

    const int LARGEUR_FENETRE = 800;
    const int HAUTEUR_FENETRE = 600;
    const int TAILLE_HUD = 16;
    const int TAILLE_CARRE = 20;
    const int TIME_GAME = 120;
    bool first = true;

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

    Text staticScore;
    staticScore.setFont(fontOldSchool);
    staticScore.setString("Nombre de points:");
    staticScore.setCharacterSize(TAILLE_HUD);
    staticScore.setColor(Color::White);
    staticScore.setPosition(400,0);

    Text score;
    score.setFont(fontOldSchool);
    score.setString("0");
    score.setCharacterSize(16);
    score.setColor(Color::White);
    score.setPosition(700,0);

    Text staticTemps;
    staticTemps.setFont(fontOldSchool);
    staticTemps.setString("Temps Restant");
    staticTemps.setCharacterSize(12);
    staticTemps.setColor(Color::White);
    staticTemps.setPosition(100,0);

    Text temps;
    temps.setFont(fontOldSchool);
    temps.setString("0");
    temps.setCharacterSize(12);
    temps.setColor(Color::White);
    temps.setPosition(320,0);

    Text fin;
    fin.setFont(fontOldSchool);
    fin.setString("FELICITATION \n SCORE FINAL: ");
    fin.setCharacterSize(16);
    fin.setColor(Color::White);
    fin.setPosition(250,400);

    score.setString("0");


    /********/
    /*TEMPS*/
    /******/
    time_t tempsDepart;
    time_t tempsActuel;
    time(&tempsDepart);
    int tempsEcouler =0, timeleft;


    while (window.isOpen())
    {
        if(timeleft != 0)
        {

            time(&tempsActuel);
            if(tempsEcouler != difftime(tempsActuel,tempsDepart))
            {
                timeleft = TIME_GAME - difftime(tempsActuel,tempsDepart);
                temps.setString(to_string(timeleft));
                tempsEcouler = difftime(tempsActuel,tempsDepart);
            }


            Event event;
            while (window.pollEvent(event))
            {       
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(staticTemps);
            window.draw(temps);
            window.draw(staticScore);
            window.draw(score);
            window.draw(randomRect);
            window.display();
        }
        else
        {
            if(first)
                fin.setString(fin.getString() + score.getString());
            first = false;
            window.draw(fin);
            window.display();
        }
    }

    return 0;
}
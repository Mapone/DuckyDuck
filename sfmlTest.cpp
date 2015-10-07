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
    const int HAUTEUR_FENETRE = 800;
    const int TAILLE_HUD = 16;
    const int TAILLE_CARRE = 20;
    const int TIME_GAME = 20;
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
    staticTemps.setCharacterSize(16);
    staticTemps.setColor(Color::White);
    staticTemps.setPosition(100,0);

    Text temps;
    temps.setFont(fontOldSchool);
    temps.setString("0");
    temps.setCharacterSize(16);
    temps.setColor(Color::White);
    temps.setPosition(320,0);

    Text fin;
    fin.setFont(fontOldSchool);
    fin.setString("FELICITATION \n SCORE FINAL: ");
    fin.setCharacterSize(16);
    fin.setColor(Color::White);
    fin.setPosition(250,400);


    int randomX = rand() % (LARGEUR_FENETRE-TAILLE_CARRE);
    int randomY = rand() % (HAUTEUR_FENETRE-TAILLE_CARRE);

    RectangleShape randomRect(Vector2f(TAILLE_CARRE,TAILLE_CARRE));
    randomRect.setFillColor(Color::Red);
    randomRect.setPosition(randomX,randomY);

    score.setString("0");


    cout << randomRect.getPosition().x << endl;
    cout << randomRect.getPosition().y << endl;

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


            if (Mouse::isButtonPressed(Mouse::Left))
            {

                Vector2i position = Mouse::getPosition(window);

                cout << position.x << endl;
                cout << position.y << endl;
                if(position.x>= randomRect.getPosition().x && position.x<= (randomRect.getPosition().x+TAILLE_CARRE))
                {
                    if(position.y>= randomRect.getPosition().y && position.y<= (randomRect.getPosition().y+TAILLE_CARRE))
                    {
                        updateScore(10, score);
                        randomX = rand() % (LARGEUR_FENETRE-TAILLE_CARRE);
                        randomY = rand() % (HAUTEUR_FENETRE-TAILLE_CARRE)+TAILLE_HUD;
                        randomRect.setPosition(randomX,randomY);
                    }
                   
                }
            }
    /*
            if(i_score%20==0)
            {
            }*/

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
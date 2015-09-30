#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////


//----------------------Fenetre----------------------
//----------------------------------------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Ouverture de la fenêtre principale
    sf::RenderWindow window(sf::VideoMode(800, 800), "DuckyDuck",sf::Style::Default, settings);
    //Limite à 60fps
    window.setFramerateLimit(60);

//----------------------Police------------------------
//----------------------------------------------------

    sf::Font fontOldSchool;
    if (!fontOldSchool.loadFromFile("gamefont.ttf"))
        cout << "#ERROR: Erreur lors du chargement de la police \"gamefont.tff\" " << endl;

    sf::Text staticScore;
    staticScore.setFont(fontOldSchool);
    staticScore.setString("Nombre de points:");
    staticScore.setCharacterSize(16);
    staticScore.setColor(sf::Color::White);
    staticScore.setPosition(400,0);

    sf::Text score;
    score.setFont(fontOldSchool);
    score.setString("0");
    score.setCharacterSize(16);
    score.setColor(sf::Color::White);
    score.setPosition(700,0);

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

        window.clear();
        window.draw(staticScore);
        window.draw(score);
        window.display();
    }

    return 0;
}
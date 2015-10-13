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


class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * width];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                //cout << tu << " = " << tileNumber << " modulo " << m_tileset.getSize().x << "/" << tileSize.x << endl;
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x+tu, tv * tileSize.y+tv);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x+tu, tv * tileSize.y+tv);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x+tu, (tv + 1) * tileSize.y+tv);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x+tu, (tv + 1) * tileSize.y+tv);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};




int main()
{
    ////////////////////////////////////
    ////////////INITIALISATION//////////
    ////////////////////////////////////

    const int LARGEUR_FENETRE = 320;
    const int HAUTEUR_FENETRE = 240;
    const int TAILLE_HUD = 16;
    const int TAILLE_CARRE = 20;
    const int TIME_GAME = 120;

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

    int level[] = { 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    1,0,0,0,0,0,0,0,0,1,1,1,1,1,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,3,4,0,0,0,2,2,2,2,0,0,24,24, 
    0,0,5,6,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,5,6,0,0,0,0,0,0,0,0,0,0,0, 
    0,0,5,6,35,0,0,42,0,0,60,0,0,0,0, 
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}; 

      TileMap map;
    if (!map.load("tileset2.png", sf::Vector2u(16, 16), level, 15, 13))
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
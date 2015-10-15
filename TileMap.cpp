#include <iostream>
#include <stdint.h> //uint8
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

using namespace std;

TileMap::TileMap(sf::Image niveau)
{
    level = new int[niveau.getSize().x*niveau.getSize().y];
    level = loadBMP(niveau);
}

TileMap::~TileMap()
{
    delete level;
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
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

int * TileMap::getLevel()
{
    return level;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}

int *TileMap::loadBMP(sf::Image niveau)
{

    if(!niveau.loadFromFile("lvl2.bmp"))
        cout << "#ERROR: Erreur lors du chargement du niveau \"lvl1.bmp\" " << endl;

    const uint8_t *t;
    t = niveau.getPixelsPtr();
    int *lvl = new int[niveau.getSize().x*niveau.getSize().y];

    for (unsigned int i = 0; i < (niveau.getSize().x*niveau.getSize().y*4); i+=4)
    {
        cout <<" RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << endl;

        if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 200)
            lvl[i/4] = 52; //BLOC CIEL

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 200 && static_cast<int>(t[i+2]) == 0)
            lvl[i/4] = 192; //BLOC HERBE

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 100 && static_cast<int>(t[i+2]) == 0)
            lvl[i/4] = 191; //BLOC HERBE BORDURE GAUCHE

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
            lvl[i/4] = 194; //BLOC HERBE BORDURE DROITE

        else if( static_cast<int>(t[i]) == 176 && static_cast<int>(t[i+1]) == 176 && static_cast<int>(t[i+2]) == 176)
            lvl[i/4] = 183; //BLOC PIERRE NON TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 96 && static_cast<int>(t[i+2]) == 96)
            lvl[i/4] = 122; //BLOC PIERRE TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 56 && static_cast<int>(t[i+2]) == 48)
            lvl[i/4] = 195; //BLOC TERRE

        else if( static_cast<int>(t[i]) == 138 && static_cast<int>(t[i+1]) == 81 && static_cast<int>(t[i+2]) == 70)
            lvl[i/4] = 198; //BLOC DEMI-TERRE SUR LA GAUCHE

        else if( static_cast<int>(t[i]) == 63 && static_cast<int>(t[i+1]) == 38 && static_cast<int>(t[i+2]) == 34)
            lvl[i/4] = 197; //BLOC DEMI-TERRE SUR LA DROITE

        else
        {
            cout << "#ERROR: loadBMP(niveau), couleur non existante RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << endl;
            break; 
        }
    }
    for (unsigned int j = 0; j < niveau.getSize().y*niveau.getSize().x; ++j)
    {
        if(j%niveau.getSize().x == 0)
            cout << endl;
        cout << lvl[j];
    }
    return lvl;
}
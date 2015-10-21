#include <iostream>
#include <stdint.h> //uint8
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

using namespace std;

TileMap::TileMap(string levelName)
{
    sf::Image niveau;
    if(!niveau.loadFromFile(levelName))
        cout << "#ERROR: Erreur lors du chargement du niveau \"" + levelName + "\" " << endl;


    mapCollisions = new bool[niveau.getSize().x*niveau.getSize().y*4];
    level = new int[niveau.getSize().x*niveau.getSize().y];

    width = niveau.getSize().x;
    height = niveau.getSize().y;

    loadBMP(niveau);
}

TileMap::~TileMap()
{
    delete level;
    delete mapCollisions;
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles)
{
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;
    
    // Tableau donnant la nature du bloc généré (plein, demi/quart de bloc)
    int sizeBlocs[]=
    {
        1,1,0,0,0,0,0,0,1,1,0,0,3,4,3,4,5,6,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,9,
        8,7,0,0,0,0,0,0,0,0,0,0,0,0,9,0,9,9,
        1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,3,4,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,
        0,0,0,0,0,0,0,4,3,0,0,9,1,0,1,1,9,9,
        9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9
    };
    
    
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
    {
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
            
            // Si le bloc n'est pas plein, on doit le définir en tant que demi/quart de bloc
            
            cout << i << ":" << j << endl;
            cout << i + j * width << ":" << level[i + j * width] << endl;
            
            switch(level[i + j * width])
            {
                case 52:
                    mapCollisions[i + j * width] = 1;
                    break;

                case 122:
                    mapCollisions[i + j * width] = 1;
                    break;

                default:
                    mapCollisions[i + j * width] = 0;
                    break;
            }




            /*
            switch(sizeBlocs[tileNumber])
            {
                // Bloc Plein
                case 0:
                    mapCollisions[(i+j*width)]=true;
                    mapCollisions[(i+j*width)+1]=true;
                    mapCollisions[(i+j*width)+2]=true;
                    mapCollisions[(i+j*width)+3]=true;
                    break;

                // Bloc 8x16 partie Basse
                case 1:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=true;
                    mapCollisions[(i+j*width)+3]=true;
                    break;

                // Bloc 8x16 partie Haute
                case 2:
                    mapCollisions[(i+j*width)]=true;
                    mapCollisions[(i+j*width)+1]=true;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=false;
                    break;

                // Bloc 16x8 partie Gauche
                case 3:
                    mapCollisions[(i+j*width)]=true;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=true;
                    break;

                // Bloc 16x8 partie Droite
                case 4:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=true;
                    mapCollisions[(i+j*width)+2]=true;
                    mapCollisions[(i+j*width)+3]=false;
                    break;

                // Bloc 8x8 Haut Gauche
                case 5:
                    mapCollisions[(i+j*width)]=true;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=false;
                    break;

                // Bloc 8x8 Haut Droit
                case 6:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=true;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=false;
                    break;
           
                // Bloc 8x8 Bas Gauche
                case 7:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=true;
                    break;

                // Bloc 8x8 Bas Droit
                case 8:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=true;
                    mapCollisions[(i+j*width)+3]=false;
                    break;

                // Bloc Transparent
                case 9:
                    mapCollisions[(i+j*width)]=false;
                    mapCollisions[(i+j*width)+1]=false;
                    mapCollisions[(i+j*width)+2]=false;
                    mapCollisions[(i+j*width)+3]=false;
                    break;
                
                default:
                    cout << "ERROR : sizeBlocs ne contient pas la nature du bloc : " << tileNumber << endl;
                    break;
            }*/
		}        
	}
    return true;
}

int * TileMap::getLevel()
{
    return level;
}


bool TileMap::collision(const sf::RectangleShape& shape, const sf::Vector2f& vect)
{
    int i,j;
    bool hautGauche, hautDroite, basGauche, basDroite;

    i = (shape.getPosition().x + vect.x)/16;   
    j = (shape.getPosition().y + vect.y)/16;
    hautGauche = mapCollisions[i+j*width];

    i = (shape.getPosition().x + vect.x)/16;   
    j = (shape.getPosition().y + shape.getSize().y + vect.y)/16;
    hautDroite = mapCollisions[i+j*width];

    i = (shape.getPosition().x + shape.getSize().x + vect.x)/16;   
    j = (shape.getPosition().y + vect.y)/16;
    basGauche = mapCollisions[i+j*width];

    i = (shape.getPosition().x + shape.getSize().x + vect.x)/16;   
    j = (shape.getPosition().y + shape.getSize().y + vect.y)/16;
    basDroite = mapCollisions[i+j*width];

    return hautGauche && hautDroite && basDroite && basGauche;
}
bool TileMap::collisionBas(const sf::RectangleShape& shape, const sf::Vector2f& vect)
{
    int i,j;
    bool basGauche, basDroite;
    i = (shape.getPosition().x + shape.getSize().x + vect.x)/16;   
    j = (shape.getPosition().y + vect.y)/16;
    basGauche = mapCollisions[i+j*width];

    i = (shape.getPosition().x + shape.getSize().x + vect.x)/16;   
    j = (shape.getPosition().y + shape.getSize().y + vect.y)/16;
    basDroite = mapCollisions[i+j*width];

    return basDroite && basGauche;
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

void TileMap::loadBMP(sf::Image niveau)
{

    const uint8_t *t;
    t = niveau.getPixelsPtr();

    for (unsigned int i = 0; i < (niveau.getSize().x*niveau.getSize().y*4); i+=4)
    {
        //cout <<" RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << endl;

        if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 200)
            level[i/4] = 52; //BLOC CIEL

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 200 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 192; //BLOC HERBE

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 100 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 191; //BLOC HERBE BORDURE GAUCHE

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 194; //BLOC HERBE BORDURE DROITE

        else if( static_cast<int>(t[i]) == 176 && static_cast<int>(t[i+1]) == 176 && static_cast<int>(t[i+2]) == 176)
            level[i/4] = 183; //BLOC PIERRE NON TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 96 && static_cast<int>(t[i+2]) == 96)
            level[i/4] = 122; //BLOC PIERRE TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 56 && static_cast<int>(t[i+2]) == 48)
            level[i/4] = 195; //BLOC TERRE

        else if( static_cast<int>(t[i]) == 138 && static_cast<int>(t[i+1]) == 81 && static_cast<int>(t[i+2]) == 70)
            level[i/4] = 198; //BLOC DEMI-TERRE SUR LA GAUCHE

        else if( static_cast<int>(t[i]) == 63 && static_cast<int>(t[i+1]) == 38 && static_cast<int>(t[i+2]) == 34)
            level[i/4] = 197; //BLOC DEMI-TERRE SUR LA DROITE

        else
        {
            cout << "#ERROR: loadBMP(niveau), couleur non existante RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << endl;
            break; 
        }
    }
}
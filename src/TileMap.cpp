#include <iostream>
#include <string>
#include <stdint.h> //uint8
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

using namespace std;

TileMap::TileMap(string levelName, sf::Vector2f &gravity)
{
    _levelName = levelName;
    _gravity = gravity;
    string img_level = levelName + ".bmp";
    string layer_level = levelName + "_layer.bmp";
    sf::Image niveau, layer;
    if(!niveau.loadFromFile(img_level))
        cerr << "#ERROR: Erreur lors du chargement du niveau \"" + img_level + "\" " << endl;

    if(!layer.loadFromFile(layer_level))
        cerr << "#ERROR: Erreur lors du chargement du layer \"" + layer_level + "\" " << endl;

    //Initialisation des tableaux et variables
    mapCollisions = new bool[niveau.getSize().x*niveau.getSize().y*4];
    level = new int[niveau.getSize().x*niveau.getSize().y];

    //_spawn et _levelEnd sont initialisé avec des valeures impossibles
    _spawn.x = -1;
    _levelEnd.setPosition(-1,-1);

    width = niveau.getSize().x;
    height = niveau.getSize().y;

    loadBMP(niveau);
    loadLayer(layer);

    if (!load("tileset2spawn.png", sf::Vector2u(16, 16)))
        cerr << "#ERROR: Erreur lors du chargement du tileset" << endl;
}

TileMap::~TileMap()
{
    delete level;
    delete mapCollisions;
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize)
{
    const int* tiles = level;
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;
    //m_tileset.setSmooth(true);
    
    
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
            
            switch(level[i + j * width])
            {
                case 2:
                    mapCollisions[i + j * width] = 0;
                    break;

                case 122:
                    mapCollisions[i + j * width] = 0;
                    break;

                default:
                    mapCollisions[i + j * width] = 1;
                    break;
            }
        }        
    }
    return true;
}

int * TileMap::getLevel()
{
    return level;
}


sf::Vector2f TileMap::getSpawn() const
{
    return _spawn;
}

string TileMap::getLevelName() const
{
    return _levelName;
}


bool TileMap::collision(const sf::Vector2f& point, const sf::Vector2f& vect)
{   
   /* if(point.x<-0.5 || point.x>width*16+0.5 || point.y < -0.5 || point.y >height*16)
        return true;*/
    int i,j;
    i = (point.x + vect.x - getPosition().x)/16;   
    j = (point.y + vect.y - getPosition().y)/16;
    return mapCollisions[i+j*width];
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);

    target.draw(_levelEnd);
}

void TileMap::loadBMP(sf::Image niveau)
{

    const uint8_t *t;
    t = niveau.getPixelsPtr();

    for (unsigned int i = 0; i < (niveau.getSize().x*niveau.getSize().y*4); i+=4)
    {
        if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 200)
            level[i/4] = 2; //BLOC CIEL

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

        else if( static_cast<int>(t[i]) == 255 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
        {
            level[i/4] = 2; //BLOC DE SPAWN, on place donc un bloc ciel
            int j = i/4;
            _spawn.x = (j%width)* 16;
            _spawn.y = ((int)(j/width)+1)* 16;
        }
        else
        {
            cerr << "#ERROR: loadBMP(niveau), couleur non existante RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << endl;
            break; 
        }
    }
}
void TileMap::loadLayer(sf::Image layer)
{
    const uint8_t *t;
    t = layer.getPixelsPtr();

    for (unsigned int i = 0; i < (layer.getSize().x*layer.getSize().y*4); i+=4)
    { 
        //Si on est sur la couleur "transparent" (0,0,0,0), on passe au prochain tour de boucle
        int check = static_cast<int>(t[i]) + static_cast<int>(t[i+1]) + static_cast<int>(t[i+2]) + static_cast<int>(t[i+3]);
        if(!check)
            continue;

        if( static_cast<int>(t[i]) == 255 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
        {
            //POINT DE SPAWN
            int j = i/4;
            _spawn.x = (j%width)* 16;
            _spawn.y = ((int)(j/width)+1)* 16;
        }

        else if( static_cast<int>(t[i]) == 255 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 255)
        {
            //BLOC DE FIN DE NIVEAU
            int j = i/4;
            _levelEnd.setSize(sf::Vector2f(16,16));
            if(!flag.loadFromFile("flag.png"))
                cerr << "#ERROR: Erreur lors du chargement de la texture \"flag.png\"" << endl;
            _levelEnd.setTexture(&flag, true);
            _levelEnd.setPosition((j%width)* 16 , (((int)(j/width)+1)* 16) - _levelEnd.getSize().y);
        }
        else
        {
            int j,k,l;
            j = i/4;
            k = (j%width)* 16;
            l = ((int)(j/width)+1)* 16;
            cerr << "#ERROR: loadLayer(layer), couleur non existante RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << " en position " << k << ":" << l <<endl;
        }
    }

    if(_spawn.x == -1)
                cerr << "#ERROR: Pas de spawn trouvé pour \"" + _levelName + "\"" << endl;
    if(_levelEnd.getPosition().x == -1)
                cerr << "#ERROR: Pas de fin de niveau trouvé pour \"" + _levelName + "\"" << endl;
}



sf::Vector2f TileMap::getGravity() const
{
    return _gravity;
}

unsigned int TileMap::getWidth() const
{
    return width;
}

sf::RectangleShape* TileMap::getLevelEnd() 
{
    return &_levelEnd;
}

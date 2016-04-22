#include <iostream>
#include <string>
#include <stdint.h> //uint8
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "AliveEntity.hpp"
#include "Spawner.hpp"
#include "Jumper.hpp"
#include "Follower.hpp"
#include "Boomer.hpp"
#include "EnemySpawner.hpp"
#include "Spike.hpp"
#include "InvertGravityBlock.hpp"


using namespace std;

TileMap::TileMap(string levelName, sf::Vector2f &gravity, const Personnage& p): _perso(p)
{
    _levelName = levelName;
    _initialGravity = _gravity = gravity;
    string img_level = levelName + ".png";
    string layer_level = levelName + "_layer.png";
    sf::Image niveau;
    if(!niveau.loadFromFile(img_level))
        cerr << "#ERROR: Erreur lors du chargement du niveau \"" + img_level + "\" " << endl;

    if(!_layer.loadFromFile(layer_level))
        cerr << "#ERROR: Erreur lors du chargement du layer \"" + layer_level + "\" " << endl;

    //Initialisation des tableaux et variables
    mapCollisions = new bool[(niveau.getSize().x+1)*niveau.getSize().y*4];

    for (unsigned int i = 0; i<(niveau.getSize().x+1)*niveau.getSize().y*4 ; ++i)
        mapCollisions[i] = false;


    level = new int[niveau.getSize().x*niveau.getSize().y];


    //_spawn et _levelEnd sont initialisé avec des valeures impossibles
    _spawn.x = -1;
    _levelEnd.setPosition(-1,-1);

    width = niveau.getSize().x;
    height = niveau.getSize().y;

    loadBMP(niveau);
    loadLayer(_layer);

    if (!load("tileset2.png", sf::Vector2u(16, 16)))
        cerr << "#ERROR: Erreur lors du chargement du tileset" << endl;
}

TileMap::~TileMap()
{
    delete level;
    delete mapCollisions;

    for (auto *e : _enemies)
    {
        delete e;
    }
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
            
            //Definition du tableau de collisions:
            //0 si traversable, 1 sinon
            switch(level[i + j * width])
            {
                //BLOC CIEL
                case 2:
                    mapCollisions[i + j * width] = 0;
                    break;
                //BLOC NUAGE GAUCHE
                case 3:
                    mapCollisions[i + j * width] = 0;
                    break;
                //BLOC NUAGE DROIT
                case 4:
                    mapCollisions[i + j * width] = 0;
                    break;
                //BLOC PIERRE GROTTE
                case 122:
                    mapCollisions[i + j * width] = 0;
                    break;
                //SINON
                default:
                    mapCollisions[i + j * width] = 1;
                    break;
            }
        }        
    }
    return true;
}

/**********************************************************/
/************************ COLLISIONS *********************/
/********************************************************/


bool TileMap::collision(const sf::Vector2f& point, const sf::Vector2f& vect) const
{
    int i,j;
    i = (point.x + vect.x - getPosition().x);   
    j = (point.y + vect.y - getPosition().y);

    //Cas de sortie de map (gauche, droite et haut)
    if(i < 0 || j< 0 || i > (int)(width*16-1))
        return true;
    else
        return mapCollisions[(i/16)+(j/16)*width];
}


bool TileMap::collisionHaut(const AliveEntity& ae) const
{
    bool colYHautDroit, colYHautGauche;

    sf::Vector2f position = ae.getPosition();
    sf::Vector2f size = ae.getShape().getSize();
    sf::Vector2f mvt = ae.getMouvement();

    colYHautDroit = collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(0,mvt.y));
    colYHautGauche = collision(position, sf::Vector2f(0,mvt.y));

    return colYHautDroit || colYHautGauche;
}

bool TileMap::collisionBas(const AliveEntity& ae) const
{
    bool colYBasDroit, colYBasGauche;

    sf::Vector2f position = ae.getPosition();
    sf::Vector2f size = ae.getShape().getSize();
    sf::Vector2f mvt = ae.getMouvement();

    colYBasDroit = collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(0,mvt.y));
    colYBasGauche = collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(0,mvt.y));

    return colYBasDroit || colYBasGauche;
}

bool TileMap::collisionDroite(const AliveEntity& ae) const
{
    bool colXBasDroit, colXHautDroit;

    sf::Vector2f position = ae.getPosition();
    sf::Vector2f size = ae.getShape().getSize();
    sf::Vector2f mvt = ae.getMouvement();

    colXHautDroit = collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(mvt.x,0));
    colXBasDroit = collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(mvt.x,0));

    return colXBasDroit || colXHautDroit;
}

bool TileMap::collisionGauche(const AliveEntity& ae) const
{
    bool colXHautGauche, colXBasGauche;

    sf::Vector2f position = ae.getPosition();
    sf::Vector2f size = ae.getShape().getSize();
    sf::Vector2f mvt = ae.getMouvement();

    colXHautGauche = collision(position, sf::Vector2f(mvt.x,0));
    colXBasGauche = collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(mvt.x,0));

    return colXHautGauche || colXBasGauche;
}

bool TileMap::collisionInvertGravBloc(const AliveEntity& ae) const
{
    for (auto & gb : _invertBlocks)
    {
        if(checkCollision(ae.getShape(), gb->getShape()))
            return true;
    }
    return false;
}

void TileMap::rotateGravityBlock()
{
    for (auto & gb : _invertBlocks)
    {
        gb->flipBlock();
    }  
}


bool TileMap::checkCollision(const sf::RectangleShape& s1, const sf::RectangleShape& s2) const
{
    sf::FloatRect boundingBoxS1 = s1.getGlobalBounds();
    sf::FloatRect boundingBoxS2 = s2.getGlobalBounds();

    if (boundingBoxS1.intersects(boundingBoxS2))
        return true;
    else 
        return false;
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

/**********************************************************/
/***************** CONSTRUCTION DU NIVEAU ****************/
/********************************************************/

void TileMap::loadBMP(sf::Image niveau)
{
    const uint8_t *t;
    t = niveau.getPixelsPtr();

    for (unsigned int i = 0; i < (niveau.getSize().x*niveau.getSize().y*4); i+=4)
    {
        if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 200) level[i/4] = 2; //BLOC CIEL

        else if( static_cast<int>(t[i]) == 220 && static_cast<int>(t[i+1]) == 220 && static_cast<int>(t[i+2]) == 220)
            level[i/4] = 3; //BLOC CIEL + NUAGE GAUCHE

        else if( static_cast<int>(t[i]) == 240 && static_cast<int>(t[i+1]) == 240 && static_cast<int>(t[i+2]) == 240)
            level[i/4] = 4; //BLOC CIEL + NUAGE DROIT
            
        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 200 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 6; //BLOC HERBE

        else if( static_cast<int>(t[i]) == 25 && static_cast<int>(t[i+1]) == 230 && static_cast<int>(t[i+2]) == 25)
            level[i/4] = 7; //BLOC HERBE N°2

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 100 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 13; //BLOC HERBE BORDURE GAUCHE

        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
            level[i/4] = 10; //BLOC HERBE BORDURE DROITE

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 76)
            level[i/4] = 14; //BLOC TERRE BORDURE GAUCHE

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 56 && static_cast<int>(t[i+2]) == 76)
            level[i/4] = 11; //BLOC TERRE BORDURE DROITE

        else if( static_cast<int>(t[i]) == 176 && static_cast<int>(t[i+1]) == 176 && static_cast<int>(t[i+2]) == 176)
            level[i/4] = 183; //BLOC PIERRE NON TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 96 && static_cast<int>(t[i+2]) == 96)
            level[i/4] = 122; //BLOC PIERRE TRAVERSANT 

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 56 && static_cast<int>(t[i+2]) == 48)
            level[i/4] = 5; //BLOC TERRE

        else if( static_cast<int>(t[i]) == 96 && static_cast<int>(t[i+1]) == 56 && static_cast<int>(t[i+2]) == 98)
            level[i/4] = 8; //BLOC TERRE N°2

        else if( static_cast<int>(t[i]) == 130 && static_cast<int>(t[i+1]) == 70 && static_cast<int>(t[i+2]) == 50)
            level[i/4] = 9; //BLOC TERRE N°3

        else if( static_cast<int>(t[i]) == 1 && static_cast<int>(t[i+1]) == 1 && static_cast<int>(t[i+2]) == 1)
            level[i/4] = 12; //BLOC CIEL INVISIBLE

        else if( static_cast<int>(t[i]) == 16 && static_cast<int>(t[i+1]) == 132 && static_cast<int>(t[i+2]) == 132)
            level[i/4] = 15; //BRIQUE

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

    Enemy* jumperPrototype = new Jumper(sf::Vector2f(15,15),*this, 3, 2);
    Spawner* jumperSpawner = new Spawner(jumperPrototype);

    Enemy* followerPrototype = new Follower(sf::Vector2f(15,15),*this, _perso,1, 3);
    Spawner* followerSpawner = new Spawner(followerPrototype);

    Enemy* tmp = new Jumper(sf::Vector2f(5,5),*this, 1, 3);

    Enemy* boomerPrototype = new Boomer(sf::Vector2f(15,15),*this,1,tmp);
    Spawner* boomerSpawner = new Spawner(boomerPrototype);

    Enemy* spikePrototype = new Spike(sf::Vector2f(15,15), *this);
    spikePrototype->flipVertically();
    Spawner* spikeSpawner = new Spawner(spikePrototype);


    for (unsigned int i = 0; i < (layer.getSize().x*layer.getSize().y*4); i+=4)
    {
        //Si on detecte la couleur de fond (blanc), on passe au prochain tour de boucle
        int check = static_cast<int>(t[i]) + static_cast<int>(t[i+1]) + static_cast<int>(t[i+2]);
        if(check == 765)
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
        else if( static_cast<int>(t[i]) == 255 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 0)
        {
            //JUMPER
           int j = i/4;
            Enemy* e = jumperSpawner->spawnEnemy();
            e->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16));
            _enemies.push_back(e);
        }
        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 255 && static_cast<int>(t[i+2]) == 0)
        {
            //BOOMER
           int j = i/4;
            Enemy* e = boomerSpawner->spawnEnemy();
            e->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16));
            _enemies.push_back(e);
        }
        else if( static_cast<int>(t[i]) == 127 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 127)
        {
            //FOLLOWER
            int j = i/4;
            Enemy* e = followerSpawner->spawnEnemy();
            e->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16));
            _enemies.push_back(e);
        }
        else if( static_cast<int>(t[i]) == 0 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 0)
        {
            //SPAWNER
           int j = i/4;
            Enemy* e = new EnemySpawner(*this, tmp, 3);
            e->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16));
            _enemies.push_back(e);
        }
        else if( static_cast<int>(t[i]) == 74 && static_cast<int>(t[i+1]) == 74 && static_cast<int>(t[i+2]) == 74)
        {
            //Spike
            int j = i/4;
            Enemy* e = spikeSpawner->spawnEnemy();
            e->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16 +1));
            _enemies.push_back(e);
        }
        else if( static_cast<int>(t[i]) == 127 && static_cast<int>(t[i+1]) == 0 && static_cast<int>(t[i+2]) == 0)
        {
            //INVERT_GRAVITY
            int j = i/4;
            InvertGravityBlock* invBlock = new InvertGravityBlock(sf::Vector2f(16,16));
            invBlock->setPosition(sf::Vector2f((j%width)* 16,((int)(j/width))* 16 +1));
            addInvertblock(invBlock);
        }
        else
        {
            int j,k,l;
            j = i/4;
            k = (j%width);
            l = (int)(j/width)+1;
            cerr << "#ERROR: loadLayer(layer), couleur non existante RGBA: " << static_cast<int>(t[i]) << "," << static_cast<int>(t[i+1]) << "," << static_cast<int>(t[i+2]) << "," << static_cast<int>(t[i+3]) << " en position " << k << ":" << l <<endl;
        }
    }

    if(_spawn.x == -1)
                cerr << "#ERROR: Pas de spawn trouvé pour \"" + _levelName + "\"" << endl;
    if(_levelEnd.getPosition().x == -1)
                cerr << "#ERROR: Pas de fin de niveau trouvé pour \"" + _levelName + "\"" << endl;


    delete jumperPrototype;
    delete jumperSpawner;
    delete followerPrototype;
    delete followerSpawner;
    delete boomerPrototype;
    delete boomerSpawner;
    delete spikePrototype;
    delete spikeSpawner;
}

/**********************************************************/
/*********** GETTER ET PETITES METHODES ******************/
/********************************************************/

void TileMap::addInvertblock(InvertGravityBlock* gb)
{
    _invertBlocks.push_back(gb);
}

void TileMap::changePositionX(float gap)
{
    setPosition(getPosition().x - gap, getPosition().y);
    getLevelEnd()->setPosition(getLevelEnd()->getPosition().x -gap, getLevelEnd()->getPosition().y);
    for (auto *enemy : getEnemies())
    {
        enemy->setPosition(enemy->getPosition().x - gap, enemy->getPosition().y);
    }
    for (auto gb : getBlocks())
    {
        gb->setPosition(gb->getPosition().x - gap, gb->getPosition().y);
    }
}

void TileMap::changePositionY(float gap)
{
    setPosition(getPosition().x, getPosition().y - gap);
    getLevelEnd()->setPosition(getLevelEnd()->getPosition().x, getLevelEnd()->getPosition().y - gap);
    for (auto *enemy : getEnemies())
    {
        enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y- gap);
    }
}

void TileMap::killEnemy(Enemy* e)
{
    _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), e), _enemies.end());
}

void TileMap::addEnemy(Enemy *e)
{
    _enemies.push_back(e);
}

//Retourne le début de la prochaine tuile en Y
unsigned int TileMap::nextTileY(float x) const
{
    return ((int)(x/16) + 1)*16;
} 
//Retourne la fin de la tuile précédente en Y
unsigned int TileMap::previousTileY(float x) const
{
    return ((int)(x/16))*16;
} 

//Methode rechargeant simplement le layer de la map
void TileMap::reset()
{
    for (auto *e : _enemies)
    {
        delete e;
    }
    loadLayer(_layer);
}


sf::Vector2f TileMap::getGravity() const
{
    return _gravity;
}

sf::Vector2f TileMap::getInitialGravity() const
{
    return _initialGravity;
}


void TileMap::setGravity(sf::Vector2f newGrav)
{
    _gravity = newGrav;
}

unsigned int TileMap::getWidth() const
{
    return width;
}

unsigned int TileMap::getHeight() const
{
    return height;
}

sf::RectangleShape* TileMap::getLevelEnd() 
{
    return &_levelEnd;
}

sf::Vector2f TileMap::getSpawn() const
{
    return _spawn;
}

string TileMap::getLevelName() const
{
    return _levelName;
}

std::vector<Enemy*> TileMap::getEnemies()
{
    return _enemies;
}

std::vector<InvertGravityBlock*> TileMap::getBlocks()
{
    return _invertBlocks;
}

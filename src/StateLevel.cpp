#include <iostream>
#include <vector>
#include <math.h> //floor()
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "StateLevel.hpp"
#include "StateStats.hpp"
#include "StateEscMenu.hpp"
#include "Enemy.hpp"

using namespace std;

const unsigned int LARGEUR_FENETRE = 800;
const unsigned int HAUTEUR_FENETRE = 448;
const unsigned int TAILLE_TUILE = 16;


StateLevel::StateLevel(Jeu* jeu, TileMap* tilemap, Personnage& perso) : State(jeu), _tilemap(tilemap), _perso(perso)
{}

void  StateLevel::init()
{
	_perso.setPosition(sf::Vector2f(_tilemap->getSpawn().x,_tilemap->getSpawn().y - _perso.getShape().getSize().y - 1));
    _perso.setMouvement(sf::Vector2f(0,0));
    _tilemap->setPosition(0,0);
}

void StateLevel::setLevel(TileMap* t)
{
    _tilemap = t;
    init();
}

void StateLevel::update()
{
    //On check les collisions sur la map
	checkMapCollision();

    //On check la collision avec le bloc de fin de niveau
    if(checkCollision(_perso.getShape(), *_tilemap->getLevelEnd()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        _jeu->setState(_jeu->getStateStats(true));
        return;
    }

    if(_perso.getShape().getPosition().y > 450 || collisionEnemy())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        _tilemap = _jeu->resetLevel();
        _jeu->setState(_jeu->getStateStats(false));
        return;
    }
    enemyMove();
    updateCamera();
}

bool StateLevel::collisionEnemy() const
{
    for (auto *enemy : _tilemap->getEnemies())
    {
        if(checkCollision(_perso.getShape(),enemy->getShape()))
            return true;
    }
    return false;
}

void StateLevel::enemyMove() const
{
    for (auto *enemy : _tilemap->getEnemies())
    {
        enemy->move();
    }
}

void StateLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    target.draw(*_tilemap);
    target.draw(_perso.getShape());

    for (auto *enemy : _tilemap->getEnemies())
    {
        target.draw(enemy->getShape());
    }
}

void StateLevel::pressUp()
{
	pressSpace();
}

void StateLevel::pressDown(){}
void StateLevel::pressLeft()
{
	_perso.addMouvement(sf::Vector2f(-0.2,0));
}

void StateLevel::pressRight()
{
	_perso.addMouvement(sf::Vector2f(0.2,0));
}

void StateLevel::pressSpace()
{
    //Si il y a une collision en bas, on a la droit de sauter
    bool colYBasGauche, colYBasDroit, colBas;
    sf::Vector2f position = _perso.getShape().getPosition();
    sf::Vector2f size = _perso.getShape().getSize();

    colYBasGauche = _tilemap->collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(0,1));
    colYBasDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(0,1));
    colBas = colYBasDroit || colYBasGauche;

    if(colBas)
        _perso.addMouvement(sf::Vector2f(0,-20));
}

void StateLevel::pressEsc()
{
    _jeu->setState(_jeu->getStateEscMenu());
}

void StateLevel::checkMapCollision() const
{
    //On applique d'abord la gravité au personnage
    _perso.addMouvement(_tilemap->getGravity());

    //On initialise des vecteurs pour limiter le nombre d'appels sur _perso
    sf::Vector2f position = _perso.getShape().getPosition();
    sf::Vector2f size = _perso.getShape().getSize();
    sf::Vector2f mvt = _perso.getMouvement();

    bool colHaut, colBas, colGauche, colDroite;
    bool colXHautGauche, colXHautDroit, colXBasGauche, colXBasDroit; 
    bool colYHautGauche, colYHautDroit, colYBasGauche, colYBasDroit;

    //On calcule la collision en X et en Y pour chacun des 4 points de notre rectangleShape
    colXHautGauche = _tilemap->collision(position, sf::Vector2f(mvt.x,0));
    colXHautDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(mvt.x,0));
    colXBasGauche = _tilemap->collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(mvt.x,0));
    colXBasDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(mvt.x,0));

    colYHautGauche = _tilemap->collision(position, sf::Vector2f(0,mvt.y));
    colYHautDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(0,mvt.y));
    colYBasGauche = _tilemap->collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(0,mvt.y));
    colYBasDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(0,mvt.y));

    //On en déduit les collision des cotés 
    colHaut = colYHautDroit || colYHautGauche;
    colBas = colYBasDroit || colYBasGauche;
    colGauche = colXBasGauche || colXHautGauche;
    colDroite = colXHautDroit || colXBasDroit;

    //On cherche d'ou viens la collision

    if(colGauche || colDroite)
    {
        _perso.setMouvement(sf::Vector2f(0,_perso.getMouvement().y));
    }

    if(colBas)
    {
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));
        sf::Vector2f position = _perso.getShape().getPosition();
        _perso.setPosition(sf::Vector2f( position.x ,_tilemap->nextTileY(position.y + size.y) - size.y-0.01));
    }

    if(colHaut)
    {
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));
        sf::Vector2f position = _perso.getShape().getPosition();
        _perso.setPosition(sf::Vector2f( position.x ,_tilemap->previousTileY(position.y) + 0.01));
    }

    if(!(colHaut && colBas && colDroite && colGauche))
        _perso.move(_perso.getMouvement()); 
}

bool StateLevel::checkCollision(const sf::RectangleShape& s1, const sf::RectangleShape& s2) const
{
    sf::FloatRect boundingBoxS1 = s1.getGlobalBounds();
    sf::FloatRect boundingBoxS2 = s2.getGlobalBounds();

    if (boundingBoxS1.intersects(boundingBoxS2))
        return true;
    else 
        return false;
}

void StateLevel::updateCamera() const
{
    //On définit un rectangle invisible au milieu de l'ecran
    //Si le personnage arrive sur le bord de celui ci, il faut bouger la camera (ce qui revient à deplacer la map)

    float decalX = _tilemap->getPosition().x;
    float decalY = _tilemap->getPosition().y;

    //Collision à droite de l'ecran
    if(_perso.getShape().getPosition().x >= LARGEUR_FENETRE - 300 && fabs(_tilemap->getPosition().x) + LARGEUR_FENETRE <  _tilemap->getWidth() * TAILLE_TUILE)
    {
        _tilemap->setPosition(_tilemap->getPosition().x - _perso.getMouvement().x, _tilemap->getPosition().y);
        decalX = _tilemap->getPosition().x - decalX; 
        _tilemap->getLevelEnd()->setPosition(_tilemap->getLevelEnd()->getPosition().x + decalX, _tilemap->getLevelEnd()->getPosition().y);
        for (auto *enemy : _tilemap->getEnemies())
        {
            enemy->setPosition(enemy->getPosition().x - _perso.getMouvement().x, enemy->getPosition().y);
        }
        _perso.setPosition(sf::Vector2f(LARGEUR_FENETRE - 300, _perso.getShape().getPosition().y));

    }
    //Collision à gauche
    else if(_perso.getShape().getPosition().x <= 300 && _tilemap->getPosition().x < 0)
    {
        _tilemap->setPosition(_tilemap->getPosition().x - _perso.getMouvement().x, _tilemap->getPosition().y);
        decalX = _tilemap->getPosition().x - decalX;
        _tilemap->getLevelEnd()->setPosition(_tilemap->getLevelEnd()->getPosition().x + decalX, _tilemap->getLevelEnd()->getPosition().y);
        for (auto *enemy : _tilemap->getEnemies())
        {
            enemy->setPosition(enemy->getPosition().x - _perso.getMouvement().x, enemy->getPosition().y);
        }
        _perso.setPosition(sf::Vector2f(300, _perso.getShape().getPosition().y));
    }
}
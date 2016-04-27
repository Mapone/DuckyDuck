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
#include "InvertGravityBlock.hpp"


using namespace std;

const unsigned int LARGEUR_FENETRE = 800;
const unsigned int HAUTEUR_FENETRE = 448;
const unsigned int TAILLE_TUILE = 16;


StateLevel::StateLevel(Jeu* jeu, TileMap* tilemap, Personnage& perso) : State(jeu), _tilemap(tilemap), _perso(perso)
{
    _clockInvertGravBloc.restart();
}

void  StateLevel::init()
{
	_perso.setPosition(sf::Vector2f(_tilemap->getSpawn().x,_tilemap->getSpawn().y - _perso.getShape().getSize().y - 1));
    _perso.setMouvement(sf::Vector2f(0,0));
    _tilemap->setPosition(0,0);
    _perso.setTotalScore(_perso.getTotalScore()+_perso.getCurrentScore());
    _perso.setCurrentScore(0);
    _perso.setCurrentKill(0);
}

void StateLevel::setLevel(TileMap* t)
{
    _tilemap = t;
    init();
}

void StateLevel::update()
{
    //On check les collisions entre la map est le personnage
    checkMapCollision();
    //On vérifie le scrolling de la camera
    updateCamera();
    //On vérifie ensuite la collision entre chaque ennemis présents
    checkCollision();
    //On fait ensuite bouger tous les ennemis
    enemyMove();
}

void StateLevel::checkCollision()
{
    //On check la collision avec le bloc de fin de niveau
    if(checkCollision(_perso.getShape(), *_tilemap->getLevelEnd()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        _tilemap = _jeu->resetLevel();
        _jeu->setState(_jeu->getStateStats(true));
    }

    //Si le personnage est tombé en bas du niveau ou qu'il s'est fait tuer par un ennemi
    if(_perso.getShape().getPosition().y > 450 || collisionEnemy())
    {
        //On le tue
        death();
    }

    //Bloc inversion gravité
    if(_tilemap->collisionInvertGravBloc(_perso) && _clockInvertGravBloc.getElapsedTime().asSeconds() > 0.4)
    {
        //Inversion de la texture + reset du chrono + inverse fleches + invert grav (obviousproof)
        _tilemap->setGravity(sf::Vector2f(_tilemap->getGravity().x*-1,_tilemap->getGravity().y*-1));
        _clockInvertGravBloc.restart();
        _perso.flipVertically();
        _tilemap->rotateGravityBlock();
        for (auto *enemy : _tilemap->getEnemies())
        {
            enemy->flipVertically();
        }
    }
}

void StateLevel::death()
{
    //Sleep afin d'avoir le temps de comprendre ce qui nous a tué
     std::this_thread::sleep_for(std::chrono::milliseconds(800));
    _tilemap = _jeu->resetLevel();
    _jeu->setState(_jeu->getStateStats(false));
}

bool StateLevel::collisionEnemy() const
{
    //On parcours tous les annemis de la map, on en profite pour les flip si il le faut
    for (auto *enemy : _tilemap->getEnemies())
    {
        if(collisionEnemy(enemy))
            return true;
    }
    return false;
}

bool StateLevel::collisionEnemy(Enemy *e) const
{
    bool gravPosi = _tilemap->getGravity().y > 0;
    bool jumpOn = false;
    //Si il y a collision avec le perso
    if(checkCollision(_perso.getShape(),e->getShape()))
    {
        //Si le perso est situé au dessus (ou en dessous si grav inversée) de l'ennemi, avec une marge de 5 pixels (vitesse max du perso en Y)
        if(gravPosi)
        {        
            jumpOn = (_perso.getPosition().y + _perso.getSize().y) <= e->getPosition().y + 5;
        }
        else
        {  
            jumpOn = _perso.getPosition().y >= (e->getPosition().y + e->getSize().y - 5);
        }

        if(jumpOn)
        {
            //On fait sauter le personnage
            _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,gravPosi ? -5 : 5));
            bool tmp = e->jumpOn();
            //On supprime l'ennemis si celui-ci meurt 
            if(e->isDead())
            {
                _perso.setCurrentKill(_perso.getCurrentKill() + 1);
                _perso.setCurrentScore(_perso.getCurrentScore()+e->getReward());
                _tilemap->killEnemy(e);
            }
            //On retourne le booléen de JumpOn, qui nous indique si l'on décède
            return tmp;
        }
        else
        { 
            return true;
        }
    }
    return false;
}

/*bool StateLevel::collisionEnemy(Enemy *e) const
{
    //Si il y a collision avec le perso
    if(checkCollision(_perso.getShape(),e->getShape()))
    { 
        //Si le perso est situé au dessus de l'ennemi, avec une marge de 5 pixels (vitesse max du perso en Y)
        if((_perso.getPosition().y + _perso.getSize().y) <= e->getPosition().y + 5)
        {
            //On fait cauter le personnage
            _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x, -5));
            bool tmp = e->jumpOn();
            //On supprime l'ennemis si celui-ci meurt 
            if(e->isDead())
            {
                _perso.setCurrentKill(_perso.getCurrentKill() + 1);
                _perso.setCurrentScore(_perso.getCurrentScore()+e->getReward());
                _tilemap->killEnemy(e);
            }
            //On retourne le booléen de JumpOn, qui nous indique si l'on décède
            return tmp;
        }
        else
        { 
            return true;
        }
    }
    return false;
}
*/

void StateLevel::enemyMove() const
{
    for (auto *enemy : _tilemap->getEnemies())
    {
        enemy->move();
        collisionEnemy(enemy);


        //Si il tombe dans un trou
        if(enemy->getPosition().y > _tilemap->getHeight()*16)
            _tilemap->killEnemy(enemy);
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
    for (auto block : _tilemap->getBlocks())
    {
        target.draw(block->getShape());
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
    _perso.flipLeft();
}

void StateLevel::pressRight()
{
    _perso.addMouvement(sf::Vector2f(0.2,0));
    _perso.flipRight();
}

void StateLevel::pressSpace()
{
    //Puissance du saut
    int jump = 5;
    //On regarde le sens de la gravité
    //grav négative
    if(_tilemap->getGravity().y < 0)
    {
        bool colYHautDroit, colYHautGauche;

        sf::Vector2f position = _perso.getPosition();
        sf::Vector2f size = _perso.getShape().getSize();

        colYHautDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y), sf::Vector2f(0,-1));
        colYHautGauche = _tilemap->collision(position, sf::Vector2f(0,-1));

        if(colYHautDroit || colYHautGauche)
            _perso.addMouvement(sf::Vector2f(0,jump));
    }
    //gravité positive ou nulle
    else
    {
        bool colYBasGauche, colYBasDroit;
        sf::Vector2f position = _perso.getShape().getPosition();
        sf::Vector2f size = _perso.getShape().getSize();

        colYBasGauche = _tilemap->collision(sf::Vector2f(position.x, position.y + size.y), sf::Vector2f(0,1));
        colYBasDroit = _tilemap->collision(sf::Vector2f(position.x + size.x, position.y + size.y), sf::Vector2f(0,1));

        if(colYBasDroit || colYBasGauche)
            _perso.addMouvement(sf::Vector2f(0,-jump));
    }
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
        //sf::Vector2f position = _perso.getShape().getPosition();
        //_perso.setPosition(sf::Vector2f( position.x ,(_tilemap->nextTileY(position.y + size.y) - size.y) - 0.01));
    }

    if(colHaut)
    {
        _perso.setMouvement(sf::Vector2f(_perso.getMouvement().x,0));
        //sf::Vector2f position = _perso.getShape().getPosition();
        //_perso.setPosition(sf::Vector2f( position.x ,_tilemap->previousTileY(position.y) + 0.01));
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

    //Collision à droite de l'ecran
    if(_perso.getShape().getPosition().x >= LARGEUR_FENETRE - 300 && fabs(_tilemap->getPosition().x) + LARGEUR_FENETRE <  _tilemap->getWidth() * TAILLE_TUILE)
    {
        _tilemap->changePositionX(_perso.getPosition().x - (LARGEUR_FENETRE - 300));
        _perso.setPosition(sf::Vector2f(LARGEUR_FENETRE - 300, _perso.getShape().getPosition().y));
    }
    //Collision à gauche
    else if(_perso.getShape().getPosition().x <= 300 && _tilemap->getPosition().x < 0)
    {
        _tilemap->changePositionX(_perso.getPosition().x - 300);
        _perso.setPosition(sf::Vector2f(300, _perso.getShape().getPosition().y));
    }

    //Collision en bas de l'ecran
    if(_perso.getShape().getPosition().y > HAUTEUR_FENETRE - 128 && fabs(_tilemap->getPosition().y) + HAUTEUR_FENETRE <  _tilemap->getHeight() * TAILLE_TUILE)
    {
        _tilemap->changePositionY(_perso.getPosition().y - (HAUTEUR_FENETRE - 128));
        _perso.setPosition(sf::Vector2f(_perso.getPosition().x, HAUTEUR_FENETRE - 128));
    }
    //Collision en haut de l'écran
    else if(_perso.getShape().getPosition().y <= 128 && _tilemap->getPosition().y < 0)
    {
        _tilemap->changePositionY(_perso.getPosition().y - 128);
        _perso.setPosition(sf::Vector2f(_perso.getPosition().x,128));
    }
}

#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Enemy.hpp"

class AliveEntity;
class Personnage;
/**
* \file TileMap.hpp
* \brief Gère les différentes interactions avec la map.
* 
* \author {N. Guittonneau, P. Raballand}
* \version 1.0
* \date 29/10/2015
*
* Gère toutes les interactions avec la carte joué par le jeu.
*/

/**
* \class TileMap
* \brief Classe définissant un map.
*/
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    /**
    * \brief Constructeur
    *
    * Constructeur de la classe TileMap
    *
    * \param niveau : string définissant le niveau par des tuiles, gravity : Vecteur 2D initialisant la gravité. 
    */
    TileMap(std::string niveau, sf::Vector2f &gravity, const Personnage& p);

    /**
    * \brief Destrcuteur
    *
    * Destructeur de la classe TileMap
    */
    ~TileMap();
    
    /**
    * \fn bool load(const std::string& tileset, sf::Vector2u tileSize)
    * \brief charge le niveau avec la texture de la tileset
    *
    * Fonction chargeant le niveau, en utilisant comme texture
    * la tileset prise en entrée.
    *
    * \param tileset : string contenant le nom du fichier contenant les tuiles, tileSize : taille des tuiles
    */
    bool load(const std::string& tileset, sf::Vector2u tileSize);
    
    /**
    * \fn bool collision(const sf::Vector2f& point, const sf::Vector2f& vect) const
    * \brief Vérifie la collision entre un point affecté par un vector et la map
    *
    * Vérifie si le point est en collision avec la map après son déplacement
    *
    * \param point : point à vérifier, vect : mouvement à appliquer pour la vérification
    * \return Renvoi s'il y a une collision
    */
    bool collision(const sf::Vector2f& point, const sf::Vector2f& vect) const;

    /**
    * \fn bool collisionHaut(const AliveEntity& ae) const
    * \brief Vérifie la collision sur le haut de l'AliveEntity
    *
    * Vérifie si une collision existe entre le haut du paramètre et la map
    *
    * \param ae : objet à vérifier
    * \return L'état de la collision
    */
    bool collisionHaut(const AliveEntity& ae) const;

    /**
    * \fn bool collisionBas(const AliveEntity& ae) const
    * \brief Vérifie la collision sur le bas de l'AliveEntity
    *
    * Vérifie si une collision existe entre le bas du paramètre et la map
    *
    * \param ae : objet à vérifier
    * \return L'état de la collision
    */
    bool collisionBas(const AliveEntity& ae) const;

    /**
    * \fn bool collisionDroite(const AliveEntity& ae) const
    * \brief Vérifie la collision sur la droite de l'AliveEntity
    *
    * Vérifie si une collision existe entre la droite du paramètre et la map
    *
    * \param ae : objet à vérifier
    * \return L'état de la collision
    */
    bool collisionDroite(const AliveEntity& ae) const;

    /**
    * \fn bool collisionGauche(const AliveEntity& ae) const
    * \brief Vérifie la collision sur la gauche de l'AliveEntity
    *
    * Vérifie si une collision existe entre la gauche du paramètre et la map
    *
    * \param ae : objet à vérifier
    * \return L'état de la collision
    */
    bool collisionGauche(const AliveEntity& ae) const;

    
    /**
    * \fn unsigned int getWidth() const
    * \brief Getter de Width
    *
    * Retourne la largeur du Level.
    *
    * \return La largeur du Level.
    */
    unsigned int getWidth() const;

    /**
    * \fn unsigned int getHeight() const
    * \brief Getter de Height
    *
    * Retourne la hauteur du Level.
    *
    * \return La hauteur du Level.
    */
    unsigned int getHeight() const;

    /**
    * \fn sf::Vector2f getGravity() const
    * \brief Getter de la Gravité
    *
    * Retourne la valeur (2D) de la gravité.
    *
    * \return Un Vector2f de la Gravité.
    */
    sf::Vector2f getGravity() const;

    /**
    * \fn sf::Vector2f getSpawn() const;
    *\brief Getter des coordonnées de spawn 
    *
    *\return Un Vector2f du spawn.
    */
    sf::Vector2f getSpawn() const;

    /**
    * \fn sf::RectangleShape* getLevelEnd()
    * \brief Getter de la fin du niveau
    *
    * Récupère la RectangleShape du bloc de fin de niveau
    *
    * \return La RectangleShape de fin de niveau
    */
    sf::RectangleShape* getLevelEnd();

    /**
    * \fn std::string getLevelName() const
    * \brief Getter du nom du niveau
    *
    * Récupère le nom du niveau en cours
    *
    * \return Le nom du niveau  
    */
    std::string getLevelName() const;

    /**
    * \fn std::vector<Enemy*> getEnemies()
    * \brief Getter des ennemis
    *
    * Récupère un vector contenant la liste
    * de tout les ennemis de la TileMap
    *
    * \return La liste des ennemis de la map
    */
    std::vector<Enemy*> getEnemies();

    /**
    * \fn unsigned int nextTileY(float x) const
    * \brief Retourne la tuile suivante
    *
    * Renvoi le pixel ou commence la tuile
    * suivant celle en parametre
    *
    * \return La tuile suivante
    */
    unsigned int nextTileY(float x) const;

    /**
    * \fn unsigned int previousTileY(float x) const
    * \brief Retourne la tuile précédante
    *
    * Renvoi le pixel ou commence la tuile
    * précédant celle en parametre
    *
    * \return La tuile précédante
    */
    unsigned int previousTileY(float x) const;

    /**
    * \fn void reset()
    * \brief Réinitialise la map
    *
    * Supprime tout les ennemis
    * et recharge le layer
    */
    void reset();

    /**
    * \fn void changePositionX(float gap)
    * \brief Décale tout les objets de la TileMap
    *
    * Décale tout de gap pixels en X
    *
    * \param gap : valeur du décalage
    */
    void changePositionX(float gap);

    /**
    * \fn void changePositionY(double gap)
    * \brief Décale tout les objets de la TileMap
    *
    * Décale tout de gap pixels en Y
    *
    * \param gap : valeur du décalage
    */
    void changePositionY(float gap);

    /**
    * \fn void killEnemy(Enemy*e)
    * \brief Supprime l'Enemy tué
    *
    * Supprime un ennemi lors de sa mort
    *
    * \param e : ennemi tué
    */
    void killEnemy(Enemy* e);

    /**
     * @brief Ajoute un enemy au niveau
     * @details Ajoute un enemy au niveau
     * 
     * @param e L'ennemi à ajouter
     */
    void addEnemy(Enemy *e);

private:

    /**
    * \brief Dessine un objet
    *
    * Procédure dessinant le personnage en paramètre.
    *
    * \param target : objet à afficher, states : applique la transformation (SFML Function)
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    /**
    * \fn void loadBMP(sf::Image niveau)
    * \brief Créer un tileset depuis une image
    *
    * Prends un image pré-défini qui correspond à un niveau
    * et le transforme en un tileset
    * utilisable par le programme.
    *
    * \param niveau : image servant de base pour créer le niveau.
    */
    void loadBMP(sf::Image niveau);

    /**
    * \fn void loadLayer(sf::Image layer)
    * \brief Ajoute les données du layer à la TileMap
    *
    * Ajoute les coordonnées du spawn, de la fin et du spawn des ennemis.
    *
    * \param layer : image du layer
    */
    void loadLayer(sf::Image layer);


    sf::VertexArray m_vertices; /** Tableau contenant le niveau */
    sf::Texture m_tileset; /** TileSet */
    int *level; /** Tableau contenant les valeurs des tuiles du niveau */
    bool *mapCollisions; /** Tableau de collisions du niveau */
    unsigned int width; /** CONST Largeur */
    unsigned int height; /** CONST Hauteur */
    sf::Vector2f _gravity; /** Gravité (2D) */
    sf::Vector2f _spawn;  /** Point de spawn, en bas à gauche de la tuile */
    sf::RectangleShape _levelEnd; /** Bloc de fin de niveau */
    sf::Texture flag; /** Texture du drapeau final */
    std::string _levelName; /** Nom du niveau */
    std::vector<Enemy*> _enemies; /** Liste des Enemy */
    sf::Image _layer; /** Layer du niveau */
    const Personnage& _perso;/** Le personnage principal, necessaire pour la création de certains ennemis*/
};
#endif
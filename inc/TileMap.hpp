#ifndef TILEMAP_H
#define TILEMAP_H

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
    TileMap(std::string niveau, sf::Vector2f &gravity);

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
    * \fn int *getLevel()
    * \brief Getter du Level
    *
    * Fonction renvoyant le niveau qui est en cours.
    *
    * \return Le Level en cours.
    */
    int *getLevel();
    bool collision(const sf::Vector2f& point, const sf::Vector2f& vect);
    
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
private:

    /**
    * \brief Dessine un objet
    *
    * Procédure dessinant le personnage en paramètre.
    *
    * \param target : objet à afficher, states : ???
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    /**
    * \fn void loadBMP(sf::Image niveau)
    * \brief créer un tileset depuis une image
    *
    * Prends un image pré-défini qui correspond à un niveau
    * et le transforme en un tileset
    * utilisable par le programme.
    *
    * \param niveau : image servant de base pour créer le niveau.
    */
    void loadBMP(sf::Image niveau);

    sf::VertexArray m_vertices; /** Tableau contenant le niveau */
    sf::Texture m_tileset; /** TileSet */
    int *level; /** Tableau contenant les valeurs des tuiles du niveau */
    bool *mapCollisions; /** Tableau de collisions du niveau */
    unsigned int width; /** CONST Largeur */
    unsigned int height; /** CONST Hauteur */
    sf::Vector2f _gravity; /** Gravité (2D) */
    sf::Vector2f _spawn;  /** Point de spawn, en bas à gauche de la tuile */
};


#endif
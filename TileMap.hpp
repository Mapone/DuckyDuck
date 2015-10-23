#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(std::string niveau, sf::Vector2f &gravity);
	~TileMap();
    bool load(const std::string& tileset, sf::Vector2u tileSize);
	int *getLevel();
    bool collision(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    bool collisionBas(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    bool collisionHaut(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    bool collisionGauche(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    bool collisionDroite(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    sf::Vector2f getGravity();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadBMP(sf::Image niveau);
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int *level;
    bool *mapCollisions;
    unsigned int width;
    unsigned int height;
    sf::Vector2f _gravity;
};


#endif
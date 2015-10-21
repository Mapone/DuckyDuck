#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(std::string niveau);
	~TileMap();
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles);
	int *getLevel();
    bool collision(const sf::RectangleShape& shape, const sf::Vector2f& vect);
    bool collisionBas(const sf::RectangleShape& shape, const sf::Vector2f& vect);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadBMP(sf::Image niveau);
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int *level;
    bool *mapCollisions;
    unsigned int width;
    unsigned int height;
};


#endif
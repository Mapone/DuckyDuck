#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Image niveau);
	~TileMap();
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	int *getLevel();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int *loadBMP(sf::Image niveau);
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int *level;
};


#endif
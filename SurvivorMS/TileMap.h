#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap {
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::string textureFile;

	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Texture tileSheet;

	void clear();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile);
	virtual ~TileMap();

	const sf::Texture* getTileSheet() const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 

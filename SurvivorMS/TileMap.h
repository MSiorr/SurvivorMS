#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap {
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;

	std::vector<std::vector<std::vector<Tile*>>> map;

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void addTile();
	void removeTile();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 

#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap {
private:
	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int layers;
	std::string textureFile;

	sf::RectangleShape collisionBox;

	std::stack<Tile*> deferredRenderStack;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	sf::Texture tileSheet;

	//CULLING

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	void clear();

public:
	TileMap(float gridSize, int width, int height, std::string textureFile);
	virtual ~TileMap();

	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);

	void updateCollision(Entity* entity, const float& dt);
	void update(const float& dt);
	void renderDeferred(sf::RenderTarget& target);
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPos);
};

#endif 

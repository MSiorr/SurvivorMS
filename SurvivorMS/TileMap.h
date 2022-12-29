#ifndef TILEMAP_H
#define TILEMAP_H

#include "EnemySpawnerTile.h"
#include "RegularTile.h"
#include "EnemySystem.h"

class RegularTile;
class Entity;
class EnemySpawnerTile;

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
	TileMap(const std::string fileName);
	virtual ~TileMap();

	const bool tileEmpty(const int x, const int y, const int z) const;
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;
	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeF() const;
	const bool checkType(const int x, const int y, const int z, const int type) const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	void addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void addTile(const int x, const int y, const int z, const sf::IntRect& textureRect,
		const int enemyType, const int enemyAmount, const int enemyTimeToSpawn, const int enemyMaxDistance);
	void removeTile(const int x, const int y, const int z, const int type = -1);

	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateTileCollision(Entity* entity, const float& dt);
	void updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
	void update(Entity* entity, const float& dt);

	void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPos, sf::Shader* shader = NULL, sf::Vector2f playerPos = sf::Vector2f(0, 0), const bool showCollision = false);
};

#endif 

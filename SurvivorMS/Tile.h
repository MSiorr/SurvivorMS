#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING, ONTOP, ENEMYSPAWNER };

class Tile {
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const bool getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;
	const short& getType() const;

	const bool intersects(const sf::FloatRect bounds) const;
	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0,0));
};

#endif 
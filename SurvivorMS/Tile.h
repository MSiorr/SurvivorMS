#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING, ONTOP, ENEMYSPAWNER, BLOCKADE };

class Tile {
private:

protected:
	sf::Sprite shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(short type, int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		const bool collision = false);
	virtual ~Tile();

	const short& getType() const;

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool& getCollision() const;

	virtual const bool intersects(const sf::FloatRect bounds) const;

	virtual const std::string getAsString() const = 0;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0,0)) = 0;
};

#endif 
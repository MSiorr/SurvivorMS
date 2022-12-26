#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING };

class Tile {
private:

protected:
	sf::RectangleShape shape;
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

	const bool intersects(const sf::FloatRect bounds) const;
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 
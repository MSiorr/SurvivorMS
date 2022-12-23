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
	Tile(unsigned gridX, unsigned gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const std::string getAsString() const;

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 
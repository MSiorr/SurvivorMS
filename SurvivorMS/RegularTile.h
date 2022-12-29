#ifndef REGULARTILE_H
#define REGULARTILE_H

#include "Tile.h"

class RegularTile :
    public Tile {
private:

protected:

public:
	RegularTile(short type, int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		bool collision = false);
	virtual ~RegularTile();

	virtual const std::string getAsString() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
};

#endif 
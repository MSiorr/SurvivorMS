#ifndef LVLBLOCKADETILE_H
#define LVLBLOCKADETILE_H

#include "Tile.h"
#include "Player.h"

class LvLBlockadeTile :
    public Tile {
private:

	int barierLvl;


public:
	LvLBlockadeTile(int gridX, int gridY, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& textureRect,
		int barierLvl);
	virtual ~LvLBlockadeTile();

	const std::string getAsString() const;
	const int getBarierLvl() const;

	void setCollision(const bool val);

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
};

#endif // !LVLBLOCKADETILE_H
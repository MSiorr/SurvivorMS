#ifndef PICKABLE_H
#define PICKABLE_H

#include "Player.h"

enum PICKABLETYPES {COIN, EXP};

class Pickable {
protected:

	sf::Sprite sprite;

	short type;

	bool picked;

public:
	Pickable();
	~Pickable();

	const bool canPick(Player& player);
	const bool isPicked() const;

	virtual void onPick(Player& player, int& goldCount) = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos) = 0;
};

#endif
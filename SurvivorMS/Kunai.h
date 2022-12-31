#ifndef KUNAI_H
#define KUNAI_H

#include "Item.h"

class Item;

class Kunai : public Item {
private:

	sf::Texture texture;
	float speed;
	float range;
	sf::Vector2f direction;

	unsigned minDmg;
	unsigned maxDmg;

	void initVariables();

public:
	Kunai(bool weaponBool, float x, float y, sf::Texture& textureSheet, sf::Vector2f mousePosView);
	virtual ~Kunai();

	const unsigned getDamage();
	const sf::Vector2f getCenter();

	void attack(sf::Vector2f mousePosView);

	void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false);
};

#endif 
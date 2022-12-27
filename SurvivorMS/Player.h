#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player :
	public Entity {
private:

	bool attacking;

	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	AttributeComponent* getAttributeComponent();

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseExp(const int exp);
	void gainExp(const int exp);

	void updateAttack();
	void updateAnimation(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 
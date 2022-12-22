#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity {
private:

	bool attacking;

	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	void updateAttack();
	void updateAnimation(const float& dt);
	void update(const float& dt);
};

#endif 
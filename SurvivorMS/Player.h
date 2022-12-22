#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity {
private:

	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	void update(const float& dt);
};

#endif 
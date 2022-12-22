#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity {
private:

	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float dirX, const float dirY, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};

#endif
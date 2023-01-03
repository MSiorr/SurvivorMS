#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class MovementComponent;
class AnimationComponent;
class HitboxComponent;
class AttributeComponent;
class SkillComponent;

class Entity {
private:

	void initVariables();

protected:
	sf::Sprite sprite;

	bool knock;
	int knockFramesCounter;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;

public:
	Entity();
	virtual ~Entity();

	void setTexture(sf::Texture& texture);
	void createHitboxComponent(float offsetX, float offsetY, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createAttributeComponent(const unsigned lvl, const unsigned dmg, const unsigned hp);
	void createSkillComponent();
	void createAIComponent();

	virtual HitboxComponent* getHitboxComponent();
	virtual MovementComponent* getMovementComponent();
	virtual AnimationComponent* getAnimationComponent();
	virtual AttributeComponent* getAttributeComponent();
	virtual SkillComponent* getSkillComponent();

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual const float getDistance(const Entity& entity) const;

	virtual void setPosition(const float x, const float y);

	virtual void knockBack(const int framesCount);

	virtual void move(const float dirX, const float dirY, const float& dt);
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	virtual void update(const float& dt, sf::Vector2f& mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox = false) = 0;
};

#endif
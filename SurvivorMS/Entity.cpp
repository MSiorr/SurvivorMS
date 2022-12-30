#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables() {

	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->attributeComponent = nullptr;
	this->skillComponent = nullptr;
}

Entity::Entity() {

	this->initVariables();

}

Entity::~Entity() {
	
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
}

void Entity::move(const float dirX, const float dirY, const float& dt) {

	if(this->movementComponent)
		this->movementComponent->move(dirX, dirY, dt);

}

void Entity::setTexture(sf::Texture& texture) {

	this->sprite.setTexture(texture);

}

const sf::Vector2f& Entity::getPosition() const {

	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const {

	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + sf::Vector2f(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height / 2.f
		);

	return this->sprite.getPosition() + sf::Vector2f(
		this->sprite.getGlobalBounds().width / 2.f,
		this->sprite.getGlobalBounds().height / 2.f
	);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {

	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const {

	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const {

	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const float Entity::getDistance(const Entity& entity) const {

	return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
}

void Entity::setPosition(const float x, const float y) {

	if (this->hitboxComponent)
		return this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::createHitboxComponent(float offsetX, float offsetY, float width, float height) {
	this->hitboxComponent = new HitboxComponent(this->sprite, offsetX, offsetY, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& textureSheet) {
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::createAttributeComponent(const unsigned lvl) {
	this->attributeComponent = new AttributeComponent(lvl);
}

void Entity::createSkillComponent() {
	this->skillComponent = new SkillComponent();
}

void Entity::stopVelocity() {

	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX() {

	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY() {

	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}
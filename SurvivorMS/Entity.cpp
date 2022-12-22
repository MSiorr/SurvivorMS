#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables() {

	this->movementComponent = nullptr;
}

Entity::Entity() {

	this->initVariables();

}

Entity::~Entity() {
	
	delete this->movementComponent;
	delete this->animationComponent;
}

void Entity::move(const float dirX, const float dirY, const float& dt) {

	if(this->movementComponent)
		this->movementComponent->move(dirX, dirY, dt);

}

void Entity::setTexture(sf::Texture& texture) {

	this->sprite.setTexture(texture);
	//this->sprite.setScale(4, 4);

}

void Entity::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& textureSheet) {
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::update(const float& dt) {

}

void Entity::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}
#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables() {

	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementComponent = nullptr;
}

Entity::Entity() {

	this->initVariables();

}

Entity::~Entity() {
	delete this->sprite;
}

void Entity::move(const float& dt, const float dirX, const float dirY) {

	if (this->sprite) {
		//float mX = dirX * this->moveSpeed * dt;
		//float mY = dirY * this->moveSpeed * dt;

		//this->sprite->move(mX, mY);

		this->movementComponent->move(dirX, dirY);
		this->sprite->move(this->movementComponent->getVelocity() * dt);

	}

}

void Entity::createSprite(sf::Texture* texture) {

	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
	this->sprite->setScale(4, 4);

}

void Entity::setPosition(const float x, const float y) {
	if (this->sprite) {
		this->sprite->setPosition(x, y);
	}
}

void Entity::createMovementComponent(const float maxVelocity) {
	this->movementComponent = new MovementComponent(maxVelocity);
}

void Entity::update(const float& dt) {

}

void Entity::render(sf::RenderTarget* target) {
	if(this->sprite)
		target->draw(*this->sprite);
}
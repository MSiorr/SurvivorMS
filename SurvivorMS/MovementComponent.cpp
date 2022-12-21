#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxVelocity) {
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent() {
}

const sf::Vector2f& MovementComponent::getVelocity() const {
	return this->velocity;
}

void MovementComponent::move(const float dirX, const float dirY) {
	this->velocity.x = this->maxVelocity * dirX;
	this->velocity.y = this->maxVelocity * dirY;
}

void MovementComponent::update(const float& dt) {
}

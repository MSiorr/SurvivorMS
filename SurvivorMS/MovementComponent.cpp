#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: maxVelocity(maxVelocity), sprite(sprite), acceleration(acceleration), deceleration(deceleration) {
}

MovementComponent::~MovementComponent() {
}

const float& MovementComponent::getMaxVelocity() const {
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const {
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const {

	switch (state) {
	case MOVEMENTSTATE::IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;
	case MOVEMENTSTATE::MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;
	case MOVEMENTSTATE::MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVEMENTSTATE::MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;
	case MOVEMENTSTATE::MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;
	case MOVEMENTSTATE::MOVING_DOWN:

		if (this->velocity.y> 0.f)
			return true;

		break;
	default:
		break;
	}

	return false;
}

void MovementComponent::move(const float dirX, const float dirY, const float& dt) {

	// ACCELERATION
	this->velocity.x += this->acceleration * dirX * dt;
	this->velocity.y += this->acceleration * dirY * dt;

	if (std::fabs(this->velocity.x) > this->maxVelocity) {
		this->velocity.x = std::signbit(this->velocity.x) ? -this->maxVelocity : this->maxVelocity;
	}

	if (std::fabs(this->velocity.y) > this->maxVelocity) {
		this->velocity.y = std::signbit(this->velocity.y) ? -this->maxVelocity : this->maxVelocity;
	}

}

void MovementComponent::update(const float& dt) {

	// DECELERATION

	if (!std::signbit(this->velocity.x)) {
		this->velocity.x = std::max(0.f, this->velocity.x - (this->deceleration * dt));
	} else {
		this->velocity.x = std::min(0.f, this->velocity.x + (this->deceleration * dt));
	}

	if (!std::signbit(this->velocity.y)) {
		this->velocity.y = std::max(0.f, this->velocity.y - (this->deceleration * dt));
	} else {
		this->velocity.y = std::min(0.f, this->velocity.y + (this->deceleration * dt));
	}

	// FINAL
	this->sprite.move(this->velocity * dt);
}

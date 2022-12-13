#include "stdafx.h"
#include "Entity.h"

Entity::Entity() {
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->shape.setFillColor(sf::Color::White);
	this->moveSpeed = 100.f;
}

Entity::~Entity() {
}

void Entity::move(const float& dt, const float dirX, const float dirY) {
	float mX = dirX * this->moveSpeed * dt;
	float mY = dirY * this->moveSpeed * dt;

	this->shape.move(mX, mY);
}

void Entity::update(const float& dt) {

}

void Entity::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}

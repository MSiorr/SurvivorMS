#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	float offsetX, float offsetY, 
	float width, float height) 
	: sprite(sprite), offsetX(offsetX), offsetY(offsetY) {

	this->hitbox.setPosition(
		this->sprite.getPosition().x + offsetX,
		this->sprite.getPosition().y + offsetY
	);

	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);

}

HitboxComponent::~HitboxComponent() {

}

const sf::Vector2f& HitboxComponent::getPosition() const {
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const {
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity) {
	
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

void HitboxComponent::setPosition(const sf::Vector2f& pos) {

	this->hitbox.setPosition(pos);

	this->sprite.setPosition(
		pos.x - this->offsetX,
		pos.y - this->offsetY
	);
}

void HitboxComponent::setPosition(const float x, const float y) {

	this->hitbox.setPosition(x,y);

	this->sprite.setPosition(
		x - this->offsetX,
		y - this->offsetY
	);
}

bool HitboxComponent::intersect(const sf::FloatRect& frect) {
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update(const float& dt) {

	this->hitbox.setPosition(
		this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY
	);
}

void HitboxComponent::render(sf::RenderTarget& target) {
	target.draw(this->hitbox);
}

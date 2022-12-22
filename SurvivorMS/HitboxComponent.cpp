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

	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setScale(4, 4);

}

HitboxComponent::~HitboxComponent() {

}

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect) {
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

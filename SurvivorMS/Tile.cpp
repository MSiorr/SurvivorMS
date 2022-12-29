#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {

	this->collision = false;
	this->type = 0;

}
Tile::Tile(short type, int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		const bool collision) {

	this->shape.setPosition(static_cast<float>(gridX) * gridSizeF, static_cast<float>(gridY) * gridSizeF);
	this->shape.setTexture(texture);
	this->shape.setTextureRect(textureRect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile() {
}

const sf::Vector2f& Tile::getPosition() const {
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const {
	return this->shape.getGlobalBounds();
}

const bool& Tile::getCollision() const {
	return this->collision;
}

const short& Tile::getType() const {
	return this->type;
}

const bool Tile::intersects(const sf::FloatRect bounds) const {
	
	return this->shape.getGlobalBounds().intersects(bounds);
}
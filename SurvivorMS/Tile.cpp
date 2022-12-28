#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {

	this->collision = false;
	this->type = 0;

}
Tile::Tile(int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
	bool collision, short type) {
	/*this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color(200,200,200,200));*/
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(gridX) * gridSizeF, static_cast<float>(gridY) * gridSizeF);
	this->shape.setTexture(texture);
	this->shape.setTextureRect(textureRect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile() {
}

const bool Tile::getCollision() const {
	return this->collision;
}

const sf::Vector2f& Tile::getPosition() const {
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const {
	return this->shape.getGlobalBounds();
}

const std::string Tile::getAsString() const {
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top 
		<< " " << this->collision << " " << this->type;

	return ss.str();
}

const short& Tile::getType() const {
	return this->type;
}

const bool Tile::intersects(const sf::FloatRect bounds) const {
	
	return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update() {
}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->shape, shader);
	} else {

		target.draw(this->shape);
	}

}

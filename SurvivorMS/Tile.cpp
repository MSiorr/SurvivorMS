#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {

}
Tile::Tile(float x, float y, float gridSizeF) {
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color(200,200,200,200));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(x, y);
}

Tile::~Tile() {
}

void Tile::update(const float& dt) {
}

void Tile::render(sf::RenderTarget& target) {

	target.draw(this->shape);

}

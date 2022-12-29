#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
	bool collision) : Tile(type, gridX, gridY, gridSizeF, texture, textureRect, collision) {

}

RegularTile::~RegularTile() {
}

const std::string RegularTile::getAsString() const {
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top
		<< " " << this->collision;

	return ss.str();
}

void RegularTile::update() {
}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->shape, shader);
	} else {

		target.draw(this->shape);
	}

}

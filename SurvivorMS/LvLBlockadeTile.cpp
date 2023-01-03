#include "stdafx.h"
#include "LvLBlockadeTile.h"

LvLBlockadeTile::LvLBlockadeTile(int gridX, int gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect, int barierLvl) 
	: Tile(TileTypes::BLOCKADE, gridX, gridY, gridSizeF, texture, textureRect, true) {

	this->barierLvl = barierLvl;
}

LvLBlockadeTile::~LvLBlockadeTile() {
}

const std::string LvLBlockadeTile::getAsString() const {
	std::stringstream ss;

	/*
	x,y,z
	type
	rext x, y
	barierLvl
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->barierLvl;

	return ss.str();
}

const int LvLBlockadeTile::getBarierLvl() const {
	return this->barierLvl;
}

void LvLBlockadeTile::setCollision(const bool val) {

	this->collision = val;
}

void LvLBlockadeTile::update() {

	/*if (player.getAttributeComponent()->lvl >= this->barierLvl) {
		this->collision = false;
	}*/
}

void LvLBlockadeTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->shape, shader);
	} else {

		target.draw(this->shape);
	}
}

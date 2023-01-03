#include "stdafx.h"
#include "ExpGem.h"

ExpGem::ExpGem(sf::Vector2f pos, sf::Texture& textureSheet) {

	this->type = PICKABLETYPES::EXP;

	this->exp = 100;

	this->sprite.setPosition(pos);
	this->sprite.setTexture(textureSheet);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 134, 134));
	this->sprite.setScale(0.15f, 0.15f);
}

ExpGem::~ExpGem() {
}

void ExpGem::onPick(Player& player, int& goldCount) {

	player.getAttributeComponent()->gainExp(this->exp);
	this->picked = true;
}

void ExpGem::update(const float& dt) {
}

void ExpGem::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}
}

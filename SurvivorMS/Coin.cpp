#include "stdafx.h"
#include "Coin.h"

Coin::Coin(sf::Vector2f pos, sf::Texture& textureSheet): Pickable() {

	this->type = PICKABLETYPES::COIN;

	this->gold = 10;

	this->sprite.setPosition(pos);
	this->sprite.setTexture(textureSheet);
	this->sprite.setTextureRect(sf::IntRect(3 * 134, 0, 134, 134));
	this->sprite.setScale(0.15f, 0.15f);
}

Coin::~Coin() {
}

void Coin::onPick(Player& player, int& goldCount) {

	goldCount += this->gold;
	this->picked = true;
}

void Coin::update(const float& dt) {
}

void Coin::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}
}

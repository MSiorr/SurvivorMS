#include "stdafx.h"
#include "Meat.h"

Meat::Meat(sf::Vector2f pos, sf::Texture& textureSheet) {

	this->type = PICKABLETYPES::MEAT;

	this->hpMultipHeal = 0.3f;

	this->sprite.setPosition(pos);
	this->sprite.setTexture(textureSheet);
	this->sprite.setTextureRect(sf::IntRect(4 * 134, 0, 134, 134));
	this->sprite.setScale(0.15f, 0.15f);
}

Meat::~Meat() {
}

void Meat::onPick(Player& player, int& goldCount) {

	std::cout << player.getAttributeComponent()->hpMax * this->hpMultipHeal << "\n";

	player.getAttributeComponent()->gainHP(
		player.getAttributeComponent()->hpMax * this->hpMultipHeal
	);
	this->picked = true;
}

void Meat::update(const float& dt) {
}

void Meat::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}
}

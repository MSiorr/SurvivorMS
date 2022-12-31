#include "stdafx.h"
#include "Kunai.h"

void Kunai::initVariables() {

	this->minDmg = 2;
	this->maxDmg = 5;

	this->speed = 500.f;
	this->range = 16.f;
	this->direction.x = 0.f;
	this->direction.y = 1.f;
}


Kunai::Kunai(bool weaponBool, float x, float y, sf::Texture& textureSheet, sf::Vector2f mousePosView) 
	: Item(weaponBool) {

	this->sprite.setPosition(x, y);
	this->sprite.setTexture(textureSheet);

	this->initVariables();
	this->attack(mousePosView);
}

Kunai::~Kunai() {
}

const unsigned Kunai::getDamage() {
	return (rand() % (this->maxDmg - this->minDmg + 1)) + (this->minDmg);
}

const sf::Vector2f Kunai::getCenter() {
	
	sf::Vector2f pos;

	pos.x = this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width / 2;
	pos.y = this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height / 2;

	return pos;
}

void Kunai::attack(sf::Vector2f mousePosView) {

	float pi = 3.141592654f;

	float dX = mousePosView.x - this->getCenter().x;
	float dY = mousePosView.y - this->getCenter().y;

	float angle = atan2f(dY, dX) * 180 / pi;
	this->sprite.setRotation(angle + 90.f);

	float len = std::sqrt(pow(dX, 2) + pow(dY, 2));

	this->direction.x = dX / len;
	this->direction.y = dY / len;

	std::cout << this->direction.x << " " << this->direction.y << "\n";
}

void Kunai::update(const float& dt) {

	this->sprite.move(
		this->direction.x * this->speed * dt,
		this->direction.y * this->speed * dt
	);
}

void Kunai::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}
}

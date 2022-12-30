#include "stdafx.h"
#include "Orc.h"

void Orc::initVariables() {


}

void Orc::initAnimations() {

	this->animationComponent->addAnim("IDLE", 16.f, 0, 0, 3, 0, 52, 64);
	this->animationComponent->addAnim("RUN", 12.f, 4, 0, 7, 0, 52, 64);
}

void Orc::initGui() {

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

Orc::Orc(float x, float y, sf::Texture& textureSheet, EnemySpawnerTile& enemySpawnerTile)
	: Enemy(enemySpawnerTile) {

	this->initVariables();
	this->initGui();

	this->createHitboxComponent(13, 12, 32, 52);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(textureSheet);
	this->createAttributeComponent(1);

	//this->initComponents();
	this->setPosition(x, y);

	this->initAnimations();
}

Orc::~Orc() {
}

void Orc::takeDamage(const int damage) {

	this->attributeComponent->loseHP(damage);
}

void Orc::updateAnimation(const float& dt) {


	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT)) {

		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_LEFT)) {

		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(46.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_UP)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	} else if (this->movementComponent->getState(MOVING_DOWN)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
}

void Orc::update(const float& dt, sf::Vector2f& mousePosView) {

	this->movementComponent->update(dt);

	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update(dt);

}

void Orc::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}

	target.draw(this->hpBar);

	if (this->hitboxComponent && showHitbox)
		this->hitboxComponent->render(target);
}
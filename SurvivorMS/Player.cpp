#include "stdafx.h"
#include "Player.h"

void Player::initVariables() {

	this->attacking = false;

}

void Player::initComponents() {

	//this->createMovementComponent(200.f, 10.f, 4.f);
	
	
}

Player::Player(float x, float y, sf::Texture& textureSheet) : Entity() {

	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(0, 0, 72, 99);
	this->createMovementComponent(300.f, 2400.f, 800.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnim("IDLE", 16.f, 0, 0, 3, 0, 72, 99);
	this->animationComponent->addAnim("RUN", 12.f, 4, 0, 7, 0, 72, 99);
	this->animationComponent->addAnim("HURT", 12.f, 7, 0, 9, 0, 72, 99);

	//this->initComponents();
}

Player::~Player() {
}

void Player::updateAttack() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt) {
	
	if (this->attacking) {

		if (this->animationComponent->play("HURT", dt, true))
			this->attacking = false;
	}

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
			this->sprite.setOrigin(73.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_UP)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	} else if (this->movementComponent->getState(MOVING_DOWN)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
}

void Player::update(const float& dt) {

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update(dt);

}

void Player::render(sf::RenderTarget& target) {

	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}

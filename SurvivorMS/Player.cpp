#include "stdafx.h"
#include "Player.h"

void Player::initVariables() {
}

void Player::initComponents() {

	//this->createMovementComponent(200.f, 10.f, 4.f);
	
	
}

Player::Player(float x, float y, sf::Texture& textureSheet) : Entity() {

	this->initVariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 2400.f, 800.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnim("IDLE_RIGHT", 15.f, 0, 0, 3, 0, 16, 22);
	this->animationComponent->addAnim("RUN_RIGHT", 15.f, 4, 0, 7, 0, 16, 22);
	this->animationComponent->addAnim("HURT_RIGHT", 15.f, 8, 0, 9, 0, 16, 22);

	//this->initComponents();
}

Player::~Player() {
}

void Player::update(const float& dt) {

	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE_RIGHT", dt);
	else if(this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("RUN_RIGHT", dt);

}

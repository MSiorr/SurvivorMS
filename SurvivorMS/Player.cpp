#include "stdafx.h"
#include "Player.h"

void Player::initVariables() {
}

void Player::initComponents() {

	this->createMovementComponent(200.f);
	
}

Player::Player(float x, float y, sf::Texture* texture) : Entity() {

	this->initVariables();
	this->initComponents();

	this->createSprite(texture);
	this->setPosition(x, y);
}

Player::~Player() {
}

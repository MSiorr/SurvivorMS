#include "stdafx.h"
#include "Player.h"

void Player::initVariables() {

	this->attacking = false;

}

void Player::initComponents() {

	//this->createMovementComponent(200.f, 10.f, 4.f);
	
	
}

void Player::initAnimations() {

	this->animationComponent->addAnim("IDLE", 16.f, 0, 0, 3, 0, 46, 64);
	this->animationComponent->addAnim("RUN", 12.f, 4, 0, 7, 0, 46, 64);
	this->animationComponent->addAnim("HURT", 12.f, 7, 0, 9, 0, 46, 64);
}

Player::Player(float x, float y, sf::Texture& textureSheet) : Entity() {

	this->initVariables();


	this->createHitboxComponent(0, 0, 46, 64);
	this->createMovementComponent(300.f, 2400.f, 800.f);
	this->createAnimationComponent(textureSheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	//this->initComponents();
	this->setPosition(x, y);
	this->initAnimations();
}

Player::~Player() {
}

AttributeComponent* Player::getAttributeComponent() {
	return this->attributeComponent;
}

void Player::loseHP(const int hp) {

	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp) {

	this->attributeComponent->gainHP(hp);
}

void Player::loseExp(const int exp) {

	this->attributeComponent->loseExp(exp);
}

void Player::gainExp(const int exp) {

	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		//this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt) {
	
	/*if (this->attacking) {

		if (this->animationComponent->play("HURT", dt, true))
			this->attacking = false;
	}*/

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

void Player::update(const float& dt, sf::Vector2f& mousePosView) {

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update(dt);

}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool showHitbox) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}

	if (this->hitboxComponent && showHitbox)
		this->hitboxComponent->render(target);
}

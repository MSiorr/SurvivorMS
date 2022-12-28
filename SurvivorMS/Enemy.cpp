#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables() {

	
}

void Enemy::initAnimations() {

	this->animationComponent->addAnim("IDLE", 16.f, 0, 0, 3, 0, 52, 64);
	this->animationComponent->addAnim("RUN", 12.f, 4, 0, 7, 0, 52, 64);
}

Enemy::Enemy(float x, float y, sf::Texture& textureSheet) 
	: Entity() {

	this->initVariables();

	this->createHitboxComponent(13, 12, 32, 52);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(textureSheet);

	//this->initComponents();
	this->setPosition(x, y);
	this->initAnimations();
}

Enemy::~Enemy() {
}

void Enemy::updateAnimation(const float& dt) {


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

void Enemy::update(const float& dt, sf::Vector2f& mousePosView) {

	this->movementComponent->update(dt);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update(dt);

}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->sprite, shader);
	} else {

		target.draw(this->sprite);
	}

	if (this->hitboxComponent && showHitbox)
		this->hitboxComponent->render(target);
}


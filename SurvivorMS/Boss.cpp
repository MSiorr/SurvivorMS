#include "stdafx.h"
#include "Boss.h"

void Boss::initVariables() {

	this->noRedOnSpawn = true;
}

void Boss::initAnimations() {

	this->animationComponent->addAnim("IDLE", 16.f, 0, 0, 3, 0, 64, 64);
	this->animationComponent->addAnim("RUN", 12.f, 4, 0, 7, 0, 64, 64);
}

void Boss::initAI() {
}

void Boss::initGui() {

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(2 * 60.f, 8.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

Boss::Boss(float x, float y, sf::Texture& textureSheet, EnemySpawnerTile& enemySpawnerTile, Entity& player)
	: Enemy(enemySpawnerTile) {

	this->initVariables();
	this->initGui();

	this->sprite.setScale(2.f, 2.f);

	this->createHitboxComponent(2 * 12, 2 * 12, 2 * 40, 2 * 52);
	this->createMovementComponent(120.f, 1600.f, 500.f);
	this->createAnimationComponent(textureSheet);
	this->createAttributeComponent(1, 60, 5000);

	//this->initComponents();
	this->setPosition(x, y);

	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}

Boss::~Boss() {

	delete this->follow;
}

void Boss::takeDamage(const int damage) {

	this->attributeComponent->loseHP(damage);
}

const bool Boss::getDmgTimer() {

	if (this->noRedOnSpawn) {

		if (this->damageTimer.getElapsedTime().asMilliseconds() > this->damageTimerMax) {
			this->noRedOnSpawn = false;
		}

		return false;
	} else {

		if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax) {
			return true;
		}
	}

	return false;
}

void Boss::updateAnimation(const float& dt) {


	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_RIGHT)) {

		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(2.f, 2.f);
		}

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_LEFT)) {

		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(64.f, 0.f);
			this->sprite.setScale(-2.f, 2.f);
		}

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_UP)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	} else if (this->movementComponent->getState(MOVING_DOWN)) {

		this->animationComponent->play("RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}

	if (this->getDmgTimer()) {
		this->sprite.setColor(sf::Color::Red);
	} else {
		this->sprite.setColor(sf::Color::White);
	}
}

void Boss::update(const float& dt, sf::Vector2f& mousePosView) {

	this->movementComponent->update(dt);

	this->hpBar.setSize(sf::Vector2f(2 * 60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 8.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	this->updateAnimation(dt);

	this->hitboxComponent->update(dt);

	this->follow->update(dt);

}

void Boss::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox) {

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
#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int lvl, int dmg, int hpMax) {

	this->lvl = lvl;
	this->exp = 0;
	this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->lvl + 1, 3) - 6 * pow(this->lvl + 1, 2) + ((this->lvl + 1) * 17) - 12));
	this->attributePoints = 0;

	this->hp = hpMax;
	this->hpMax = hpMax;

	this->dmg = dmg;

	this->updateLvl();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent() {
}

void AttributeComponent::loseHP(const int hp) {

	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributeComponent::gainHP(const int hp) {

	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::gainExp(const int exp) {

	this->exp += exp;

	this->updateLvl();
}

const bool AttributeComponent::isDead() const {

	return (this->hp <= 0.f);
}

const bool AttributeComponent::toUpgrade() const {

	return this->attributePoints > 0;
}

void AttributeComponent::updateStats(const bool reset) {

	if(reset)
		this->hp = this->hpMax;
}

void AttributeComponent::updateLvl() {

	while (this->exp >= this->expNext) {

		++this->lvl;
		this->exp -= this->expNext;
		this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->lvl, 3) - 6 * pow(this->lvl, 2) + (this->lvl * 17) - 12));
		++this->attributePoints;
	}
}

std::string AttributeComponent::debugPrint() const {
	
	std::stringstream ss;

	ss << "Lvl: " << this->lvl <<
		"\n" << "Exp: " << this->exp <<
		"\n" << "Exp Next: " << this->expNext <<
		"\n" << "Attp" << this->attributePoints;

	return ss.str();
}

void AttributeComponent::update() {

	this->updateLvl();
}

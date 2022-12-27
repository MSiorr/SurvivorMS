#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int lvl) {

	this->lvl = lvl;
	this->exp = 0;
	this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->lvl + 1, 3) - 6 * pow(this->lvl + 1, 2) + ((this->lvl + 1) * 17) - 12));
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLvl();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent() {
}

void AttributeComponent::gainExp(const int exp) {

	this->exp += exp;

	this->updateLvl();
}

void AttributeComponent::updateStats(const bool reset) {

	this->hpMax			= this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->dmgMin		= this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->dmgMax		= this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence		= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;

	if(reset)
		this->hp = this->hpMax / 2;
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

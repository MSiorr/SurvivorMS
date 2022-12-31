#include "stdafx.h"
#include "Item.h"

Item::Item(bool weaponBool) {

	this->toDestroy = false;
	this->weaponBool = weaponBool;
}

Item::~Item() {
}

const bool Item::isWeapon() const {
	return this->weaponBool;
}

const bool Item::isToDestroy() const {
	return this->toDestroy;
}

void Item::setToDestroy(bool val) {
	this->toDestroy = val;
}

const sf::FloatRect Item::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

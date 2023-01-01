#include "stdafx.h"
#include "Pickable.h"

Pickable::Pickable() {

	this->type = PICKABLETYPES::COIN;
	this->picked = false;
}

Pickable::~Pickable() {
}

const bool Pickable::canPick(Player& player) {
	return player.getGlobalBounds().intersects(this->sprite.getGlobalBounds());
}

const bool Pickable::isPicked() const {
	return this->picked;
}

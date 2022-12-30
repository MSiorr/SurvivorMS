#include "stdafx.h"
#include "Kunai.h"

void Kunai::initVariables() {

	this->attackTimer.restart();
	this->attackTimerMax = 500;

	this->minDmg = 2;
	this->maxDmg = 5;
}

Kunai::Kunai() : Item() {


	this->initVariables();
}

Kunai::~Kunai() {
}

const bool Kunai::getAttackTimer() {

	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax) {
		this->attackTimer.restart();
		return true;
	}
	return false;
}

const unsigned Kunai::getDamage() {
	return (rand() % (this->maxDmg - this->minDmg + 1)) + (this->minDmg);
}

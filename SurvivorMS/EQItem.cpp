#include "stdafx.h"
#include "EQItem.h"

int EQItem::calcValue(int lvl) {

	if (this->statType == ATK) {
		return static_cast<int>(lvl * 10 + lvl / 5);
	} else {
		return static_cast<int>(lvl * 30 + lvl / 8);
	}
}

int EQItem::calcCost() {
	
	return static_cast<int>(lvl * 100 + static_cast<int>(lvl / 5) * 10);
}

EQItem::EQItem(short statType, int lvl) {

	this->statType = statType;
	this->lvl = lvl;
	this->statValue = this->calcValue(this->lvl);
	this->cost = this->calcCost();
}

EQItem::~EQItem() {
}

const short& EQItem::getType() const {
	return this->statType;
}

const std::string EQItem::getTypeString() const {
	if (this->statType == ATK)
		return "ATK";
	else
		return "HP";
}

const int& EQItem::getLvl() const {
	return this->lvl;
}

const int& EQItem::getCost() const {
	return this->cost;
}

const int& EQItem::getStat() const {
	return this->statValue;
}

const int EQItem::getNextLvlStat() {
	return this->calcValue(this->lvl + 1);
}

void EQItem::lvlUp() {
	this->lvl++;
	this->statValue = this->calcValue(this->lvl);
	this->cost = this->calcCost();
}

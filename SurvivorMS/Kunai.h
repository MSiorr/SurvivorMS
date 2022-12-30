#ifndef KUNAI_H
#define KUNAI_H

#include "Item.h"

class Item;

class Kunai : public Item {
private:

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

	unsigned minDmg;
	unsigned maxDmg;

	void initVariables();

public:
	Kunai();
	virtual ~Kunai();

	const bool getAttackTimer();
	const unsigned getDamage();
};

#endif 
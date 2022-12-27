#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent {
private:

public:

	int lvl;
	int exp;
	int expNext;
	int attributePoints;

	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	int hp;
	int hpMax;

	int dmgMin;
	int dmgMax;

	int accuracy;

	int defence;

	int luck;

	AttributeComponent(int lvl);
	virtual ~AttributeComponent();

	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLvl();

	std::string debugPrint() const;

	void update();
};

#endif 
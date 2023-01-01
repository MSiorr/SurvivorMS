#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent {
private:

public:

	int lvl;
	int exp;
	int expNext;
	int attributePoints;

	int hp;
	int hpMax;

	int dmg;

	AttributeComponent(int lvl, int dmg, int hpMax);
	virtual ~AttributeComponent();

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseExp(const int exp);
	void gainExp(const int exp);

	const bool isDead() const;

	void updateStats(const bool reset);
	void updateLvl();

	std::string debugPrint() const;

	void update();
};

#endif 
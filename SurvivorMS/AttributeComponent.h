#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent {
private:

public:

	int baseHP;
	int baseDMG;
	sf::Int32 baseFireRate;

	int lvl;
	int exp;
	int expNext;
	int attributePoints;

	int hp;
	int hpMax;

	sf::Int32 fireRate;

	int dmg;

	AttributeComponent(int lvl, int dmg, int hpMax, int fireRate = 500);
	virtual ~AttributeComponent();

	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainExp(const int exp);

	const bool isDead() const;
	const bool toUpgrade() const;

	void updateStats(const float hpMultip, const float dmgMultip, const float fireRateMultip);
	void updateLvl();

	std::string debugPrint() const;

	void update();
};

#endif 
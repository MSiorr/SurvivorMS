#ifndef EQITEM_H
#define EQITEM_H

enum STATTYPE {ATK = 0, HP};

class EQItem {
private:

	short statType;
	int lvl;
	int statValue;
	int cost;

	int calcValue(int lvl);
	int calcCost();

public:
	EQItem(short statType, int lvl);
	~EQItem();

	const short& getType() const;
	const std::string getTypeString() const;
	const int& getLvl() const;
	const int& getCost() const;
	const int& getStat() const;
	const int getNextLvlStat();

	void lvlUp();

};


#endif // !



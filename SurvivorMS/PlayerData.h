#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "EQItem.h"

enum EQTYPES {
    WEAPON = 0,
    NECKLACE,
    GLOVES,
    CHESTPLATE,
    BELT,
    BOOTS
};

class PlayerData {
private:

    int gold;
    int dmg;
    int hp;

    std::map<short, EQItem*> items;

    void calcStats();
    const std::string itemsLvLToString();
public:
    PlayerData(bool newGame);
    ~PlayerData();

    const int& getDMG() const;
    const int& getHP() const;
    const int& getGold() const;
    const std::string getGoldString() const;
    const std::string getDMGString() const;
    const std::string getHPString() const;
    const std::string getItemName(short key) const;
    const std::string getItemInfo(short key) const;
    const std::string getItemCostString(short key) const;
    const int& getItemCost(short key) const;
    const bool canLvlUp(short key) const;

    void lvlUp(const short key);
    void gainGold(const short gold);
    void loseGold(const short gold);

    void saveToFile(std::string path);
    void readFromFile(std::string path, bool newGame);

};

#endif // !PLAYERDATA_H

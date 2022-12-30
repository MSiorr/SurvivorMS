#include "stdafx.h"
#include "PlayerData.h"

void PlayerData::calcStats() {

    this->dmg = 10;
    this->hp = 100;

    for (auto& item : this->items) {

        if (item.second->getType() == ATK)
            this->dmg += item.second->getStat();
        else
            this->hp += item.second->getStat();


    }
}

const std::string PlayerData::itemsLvLToString() {
    
    std::stringstream ss;

    for (auto& item : this->items) {
        ss << item.second->getLvl() << "\n";
    }

    return ss.str();

}

PlayerData::PlayerData(bool newGame) {

    this->gold = 0;

    this->readFromFile("playerData.txt", newGame);

    this->calcStats();
}



PlayerData::~PlayerData() {
}

const int& PlayerData::getGold() const {
    return this->gold;
}

const std::string PlayerData::getGoldString() const {
    std::stringstream ss;

    ss << this->gold;

    return ss.str();
}

const std::string PlayerData::getDMGString() const {
    std::stringstream ss;

    ss << "ATK: " << this->dmg;

    return ss.str();
}

const std::string PlayerData::getHPString() const {
    std::stringstream ss;

    ss << "HP: " <<  this->hp;

    return ss.str();
}

const int& PlayerData::getDMG() const {
    return this->dmg;
}

const int& PlayerData::getHP() const {
    return this->hp;
}

const std::string PlayerData::getItemName(short key) const{
    
    std::stringstream ss;

    switch (key) {
    case WEAPON:
        ss << "Weapon";
        break;
    case NECKLACE:
        ss << "Necklace";
        break;
    case GLOVES:
        ss << "Gloves";
        break;
    case CHESTPLATE:
        ss << "Chestplate";
        break;
    case BELT:
        ss << "Belt";
        break;
    case BOOTS:
        ss << "Boots";
        break;
    default:
        ss << "UNKNOWN";
        break;
    }

    return ss.str();
}

const std::string PlayerData::getItemInfo(short key) const {
    std::stringstream ss;

    ss << "Level: " << this->items.at(key)->getLvl() << "\n"
        << this->items.at(key)->getTypeString() << ": " << this->items.at(key)->getStat()
        << " (" << this->items.at(key)->getNextLvlStat() << ")";
    
    return ss.str();
}

const std::string PlayerData::getItemCostString(short key) const {
    std::stringstream ss;

    ss << this->getItemCost(key);

    return ss.str();
}

const int& PlayerData::getItemCost(short key) const {
    return this->items.at(key)->getCost();
}

const bool PlayerData::canLvlUp(short key) const {
    return this->gold >= this->items.at(key)->getCost();
}

void PlayerData::lvlUp(const short key) {

    if (this->items.at(key)) {

        if (this->canLvlUp(key)) {
            this->items.at(key)->lvlUp();
            this->loseGold(this->items.at(key)->getCost());
            this->calcStats();
        }
    } else {
        std::cout << "WRONG ITEM KEY" << "\n";
    }
}

void PlayerData::gainGold(const short gold) {
    this->gold += gold;
}

void PlayerData::loseGold(const short gold) {

    this->gold -= gold;
    if (this->gold < 0)
        this->gold = 0;
}

void PlayerData::saveToFile(std::string path) {

    /*
    format:

    gold
    weaponLvl
    necklaceLvl
    glovesLvl
    chestplateLvl
    beltLvl
    bootsLvl
    */

    std::ofstream ofs;

    ofs.open(path);

    if (ofs.is_open()) {

        ofs << this->gold << "\n";
        ofs << this->itemsLvLToString();

    }
}

void PlayerData::readFromFile(std::string path, bool newGame) {

    this->gold = 0;
    int weaponLvl = 1;
    int necklaceLvl = 1;
    int glovesLvl = 1;
    int chestplateLvl = 1;
    int beltLvl = 1;
    int bootsLvl = 1;

    std::ifstream ifs;

    ifs.open(path);

    if (ifs.is_open() && !newGame) {

        ifs >> this->gold >> weaponLvl >> necklaceLvl
            >> glovesLvl >> chestplateLvl >> beltLvl >> bootsLvl;

    }

    this->items[WEAPON] = new EQItem(STATTYPE::ATK, weaponLvl);
    this->items[NECKLACE] = new EQItem(STATTYPE::ATK, necklaceLvl);
    this->items[GLOVES] = new EQItem(STATTYPE::ATK, glovesLvl);
    this->items[CHESTPLATE] = new EQItem(STATTYPE::HP, chestplateLvl);
    this->items[BELT] = new EQItem(STATTYPE::HP, beltLvl);
    this->items[BOOTS] = new EQItem(STATTYPE::HP, bootsLvl);

    this->saveToFile(path);
}

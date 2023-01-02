#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent() {

	this->skills.push_back(Skill(SKILLS::HEALTH));
	this->skills.push_back(Skill(SKILLS::ATTACK));
	this->skills.push_back(Skill(SKILLS::FIRERATE));
}

SkillComponent::~SkillComponent() {


}

const int SkillComponent::getSkillLvl(const int skill) const {
	
	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw "ERROR:: SKILL NOT EXIST " + skill;
	else
		return this->skills[skill].getLvl();
}

const int SkillComponent::getSkillLvlCap(const int skill) const {

	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw "ERROR:: SKILL NOT EXIST " + skill;
	else
		return this->skills[skill].getLvlCap();
}

const bool SkillComponent::isSkillMaxed(const int skill) const {

	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw "ERROR:: SKILL NOT EXIST " + skill;
	else
		return this->skills[skill].maxed();
}

void SkillComponent::skillLvlUp(const int skill) {

	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw "ERROR:: SKILL NOT EXIST " + skill;
	else
		return this->skills[skill].lvlUp();
}


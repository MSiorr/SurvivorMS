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


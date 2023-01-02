#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum SKILLS {HEALTH = 0, ATTACK, FIRERATE, GOLD};

class SkillComponent {
private:

	class Skill {
	private:

		int type;
		int lvl;
		int lvlCap;

	public:
		Skill(int type) {
			
			this->type = type;
			this->lvl = 0;
			this->lvlCap = 5;
		}
		~Skill() {}

		inline const int& getType() const { return this->type; }
		inline const int& getLvl() const { return this->lvl; }
		inline const int& getLvlCap() const { return this->lvlCap; }

		inline const bool maxed() const { return this->lvl == this->lvlCap; }

		inline void setLvl(const int lvl) { this->lvl = lvl; }
		inline void setLvlCap(const int lvlCap) { this->lvlCap = lvlCap; }


		void lvlUp() {
			if (this->lvl < this->lvlCap) {

				this->lvl++;
			}
		}

		void update() {}
	};

	//std::map<std::string, Skill> skills;
	std::vector<Skill> skills;

public:
	SkillComponent();
	virtual ~SkillComponent();

	const int getSkillLvl(const int skill) const;
	const int getSkillLvlCap(const int skill) const;
	const bool isSkillMaxed(const int skill) const;

	void skillLvlUp(const int skill);
};

#endif 
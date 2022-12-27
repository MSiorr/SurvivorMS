#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum SKILLS {HEALTH = 0, ATTACK, DEFENCE};

class SkillComponent {
private:

	class Skill {
	private:

		int type;
		int lvl;
		int lvlCap;
		int exp;
		int expNext;

	public:
		Skill(int type) {
			
			this->type = type;
			this->lvl = 1;
			this->lvlCap = 5;
			this->exp = 0;
			this->expNext = 100;
		}
		~Skill() {}

		inline const int& getType() const { return this->type; }
		inline const int& getLvl() const { return this->lvl; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

		inline void setLvl(const int lvl) { this->lvl = lvl; }
		inline void setLvlCap(const int lvlCap) { this->lvlCap = lvlCap; }

		void gainExp(const int exp) { 
			this->exp += exp; 
			this->updateLvl();
		}

		void loseExp(const int exp) {
			this->exp = std::max(0, this->exp - exp);
		}

		void updateLvl() {

			if (this->lvl < this->lvlCap) {

				while (this->exp >= this->expNext) {

					if (this->lvl < this->lvlCap) {
					
						this->lvl++;
						this->expNext = this->lvl * 100 + this->lvl * 2 + static_cast<int>(std::pow(this->lvl, 2));
					}
				}
			}

		}

		void update() {}
	};

	//std::map<std::string, Skill> skills;
	std::vector<Skill> skills;

public:
	SkillComponent();
	virtual ~SkillComponent();

	const int getSkill(const int skill) const;
	const void gainExp(const int skill, const int exp);
};

#endif 
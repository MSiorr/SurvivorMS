#ifndef SKILLCHOOSE_H
#define SKILLCHOOSE_H

#include "Gui.h"

class SkillChoose {
private:

	class Skill {
	private:

		sf::VideoMode& vm;
		sf::Font& font;
		sf::RectangleShape shape;

		sf::Text titleTxt;
		sf::Text descTxt;
		sf::Text progress;

		int currLvl;
		int maxLvl;
		bool withProgress;

	public:
		Skill(sf::VideoMode& vm, sf::Font& font, 
			const std::string title, const std::string desc, 
			const int currLvl = 0, const int maxLvl = 0
		) : font(font), vm(vm) {

			if (maxLvl != 0) {

				this->currLvl = currLvl;
				this->maxLvl = maxLvl;
				this->withProgress = true;
			} else {

				this->withProgress = false;
			}

			this->shape.setFillColor(sf::Color(40, 40, 40, 200));
			this->shape.setSize(sf::Vector2f(
				gui::p2pX(9.f, vm),
				gui::p2pY(24.f, vm)
			));

			this->titleTxt.setFont(font);
			this->titleTxt.setCharacterSize(gui::calcCharSize(vm) * 0.8f);
			this->titleTxt.setString(title);

			this->descTxt.setFont(font);
			this->descTxt.setCharacterSize(gui::calcCharSize(vm) * 0.5f);
			this->descTxt.setString(desc);

			if (this->withProgress) {

				std::stringstream ss;
				ss << this->currLvl << " / " << this->maxLvl;
				this->progress.setFont(font);
				this->progress.setCharacterSize(gui::calcCharSize(vm) * 0.5f);
				this->progress.setString(ss.str());
			}
		}
		~Skill() {}

		void setPosition(const float x, const float y) {

			this->shape.setPosition(x, y);
			this->titleTxt.setPosition(
				this->shape.getPosition().x + this->shape.getSize().x / 2 - this->titleTxt.getGlobalBounds().width / 2,
				this->shape.getPosition().y + gui::p2pY(1.11f, this->vm)
			);
			this->descTxt.setPosition(
				this->shape.getPosition().x + this->shape.getSize().x / 2 - this->descTxt.getGlobalBounds().width / 2,
				this->shape.getPosition().y + gui::p2pY(8.f, this->vm)
			);
			if (this->withProgress) {

				this->progress.setPosition(
					this->shape.getPosition().x + this->shape.getSize().x / 2 - this->progress.getGlobalBounds().width / 2,
					this->shape.getPosition().y + gui::p2pY(20.f, this->vm)
				);
			}
		}

		void render(sf::RenderTarget& target) {

			target.draw(this->shape);
			target.draw(this->titleTxt);
			target.draw(this->descTxt);

			if(this->withProgress)
				target.draw(this->progress);
		}
	};

	sf::VideoMode& vm;
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape bg;
	sf::RectangleShape container;

	std::map<short, Skill*> skills;
	std::map<short, gui::Button*> buttons;

	void addButton(const short key, float x, float y, const float width, const float height, const unsigned charSize, const std::string text);
public:
	SkillChoose(sf::VideoMode& vm, sf::Font& font);
	virtual ~SkillChoose();

	std::map<short, gui::Button*>& getButtons();

	const bool isButtonPressed(const short key);
	const bool buttonExist(const short key);

	void resetSkills();

	void addSkill(const short key, const std::string title, const std::string desc, const int currLvl = 0, const int maxLvl = 0);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif // !SKILLCHOOSE_H
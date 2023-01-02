#include "stdafx.h"
#include "SkillChoose.h"

SkillChoose::SkillChoose(sf::VideoMode& vm, sf::Font& font)
	: font(font), vm(vm) {

	this->bg.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));

	this->bg.setFillColor(sf::Color(24, 24, 24, 160));


	this->container.setSize(sf::Vector2f(
		gui::p2pX(33.f, vm),
		static_cast<float>(vm.height) / 2.f 
	));

	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		static_cast<float>(vm.height) / 2.f - this->container.getSize().y / 2.f
	);

	this->container.setFillColor(sf::Color(24, 24, 24, 200));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm) * 2);
	this->menuText.setString("CHOOSE SKILL");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2pY(2.8f, vm)
	);

}

SkillChoose::~SkillChoose() {
	for (auto& it : this->buttons) {
		delete it.second;
	}

	for (auto& it : this->skills) {
		delete it.second;
	}
}

std::map<short, gui::Button*>& SkillChoose::getButtons() {
	return this->buttons;
}

const bool SkillChoose::isButtonPressed(const short key) {
	return this->buttons[key]->isPressed();
}

const bool SkillChoose::buttonExist(const short key) {
	return this->buttons.find(key) != this->buttons.end();
}

void SkillChoose::resetSkills() {

	for (auto& it : this->skills) {
		delete it.second;
	}

	for (auto& it : this->buttons) {
		delete it.second;
	}

	this->skills.clear();
	this->buttons.clear();
}

void SkillChoose::addSkill(const short key, const std::string title, const std::string desc, const int currLvl, const int maxLvl) {

	if (maxLvl == 0) 
		this->skills[key] = new Skill(this->vm, this->font, title, desc);
	else 
		this->skills[key] = new Skill(this->vm, this->font, title, desc, currLvl, maxLvl);

	float x = this->container.getPosition().x + gui::p2pX(2.f, this->vm) + (this->skills.size() - 1) * gui::p2pX(10.f, this->vm);
	float y = this->container.getPosition().y + gui::p2pY(16.f, this->vm);

	this->skills[key]->setPosition(x, y);

	this->addButton(key,
		x, y + gui::p2pY(24.5f, vm),
		gui::p2pX(9.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm) * 0.5f, "CHOOSE"
	);
}

void SkillChoose::addButton(const short key, float x, float y, const float width, const float height, const unsigned charSize, const std::string text) {

	this->buttons[key] = new gui::Button(
		x, y,
		width, height,
		&this->font, text, charSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));

}

void SkillChoose::update(const sf::Vector2i& mousePosWindow) {
	for (auto& it : this->buttons) {
		it.second->update(mousePosWindow);
	}
}

void SkillChoose::render(sf::RenderTarget& target) {
	target.draw(this->bg);
	target.draw(this->container);

	for (auto& it : this->skills) {
		it.second->render(target);
	}

	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->menuText);
}

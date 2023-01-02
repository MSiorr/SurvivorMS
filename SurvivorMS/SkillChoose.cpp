#include "stdafx.h"
#include "SkillChoose.h"

SkillChoose::SkillChoose(sf::VideoMode& vm, sf::Font& font)
	: font(font) {

	this->bg.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));

	this->bg.setFillColor(sf::Color(24, 24, 24, 160));


	this->container.setSize(sf::Vector2f(
		static_cast<float>(vm.width) / 4.f,
		static_cast<float>(vm.height) / 2.f 
	));

	this->container.setPosition(
		static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		static_cast<float>(vm.height) / 2.f - this->container.getSize().y / 2.f
	);

	this->container.setFillColor(sf::Color(24, 24, 24, 200));

	// INIT TEXT

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
}

std::map<std::string, gui::Button*>& SkillChoose::getButtons() {
	return this->buttons;
}

const bool SkillChoose::isButtonPressed(const std::string key) {
	return this->buttons[key]->isPressed();
}

void SkillChoose::addButton(const std::string key, float y, const float width, const float height, const unsigned charSize, const std::string text) {

	float x = this->container.getPosition().x + (this->container.getGlobalBounds().width / 2.f) - width / 2.f;
	y = this->container.getPosition().y + (this->container.getGlobalBounds().height / 2.f) - height / 2.f + y;

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

	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->menuText);
}

#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) 
	: font(font)
{

	this->bg.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));

	this->bg.setFillColor(sf::Color(24, 24, 24, 100));


	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) - 60.f
	));

	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->container.setFillColor(sf::Color(24, 24, 24, 200));

	// INIT TEXT

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);

}

PauseMenu::~PauseMenu() {
	for (auto& it : this->buttons) {
		delete it.second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons() {
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key) {
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text) {

	float btnWidth = 250.f, btnHeight = 50.f;

	float x = this->container.getPosition().x + (this->container.getGlobalBounds().width / 2.f) - btnWidth / 2.f;
	y = this->container.getPosition().y + (this->container.getGlobalBounds().height / 2.f) - btnHeight / 2.f + y;

	this->buttons[key] = new gui::Button(
		x,y,
		btnWidth, btnHeight,
		&this->font, text, 30,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));

}

void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
	for (auto& it : this->buttons) {
		it.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget& target) {
	target.draw(this->bg);
	target.draw(this->container);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->menuText);
}

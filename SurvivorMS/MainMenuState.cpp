#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initKeyBinds() {

	std::ifstream ifs("Config/gameStateKeyBinds.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys)
	: State(window, suppKeys) {

	this->initKeyBinds();

	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {
}

void MainMenuState::endState() {
	std::cout << "BYE BYE " << "\n";
}

void MainMenuState::updateInput(const float& dt) {
	this->checkQuit();
}

void MainMenuState::update(const float& dt) {

	this->updateInput(dt);

}

void MainMenuState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->draw(this->bg);
}

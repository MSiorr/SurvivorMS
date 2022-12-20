#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

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

void MainMenuState::initButtons() {
	this->buttons["GAME_STATE"] = new Button(50, 50, 150, 50,
		&this->font, "NEW GAME",
		sf::Color(0, 0, 0, 255), sf::Color(100, 100, 100, 255), sf::Color(255, 0, 0, 255));

	this->buttons["EXIT_STATE"] = new Button(350, 50, 150, 50,
		&this->font, "EXIT",
		sf::Color(0, 0, 0, 255), sf::Color(100, 100, 100, 255), sf::Color(255, 0, 0, 255));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys)
	: State(window, suppKeys) {

	this->initFonts();
	this->initKeyBinds();
	this->initButtons();

	this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->bg.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {

	for (auto &it : this->buttons) {
		delete it.second;
	}

}

void MainMenuState::endState() {
	std::cout << "BYE BYE " << "\n";
}

void MainMenuState::updateInput(const float& dt) {
	this->checkQuit();
}

void MainMenuState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt) {

	this->updateMousePos();

	this->updateInput(dt);

	this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
	//this->testBtn->render(target);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->draw(this->bg);

	this->renderButtons(target);
}

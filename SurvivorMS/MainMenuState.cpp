#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables() {

}

void MainMenuState::initBackground() {

	this->bg.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg.png")) {
		throw "BG LOAD ERROR";
	}

	this->bg.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

void MainMenuState::initKeyBinds() {

	std::ifstream ifs("Config/mainMenuStateKeyBinds.ini");

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
	float btnWidth = 150.f;
	float btnHeight = 50.f;
	float centerX = this->window->getSize().x / 2.f - btnWidth / 2.f;
	float centerY = this->window->getSize().y / 2.f - btnHeight / 2.f;

	this->buttons["GAME_STATE"] = new Button(
		centerX, centerY, btnWidth, btnHeight,
		&this->font, "NEW GAME",
		sf::Color(0, 0, 0, 255), sf::Color(100, 100, 100, 255), sf::Color(255, 0, 0, 255));
	
	this->buttons["SETTINGS_STATE"] = new Button(
		centerX, centerY + 1.5*btnHeight, btnWidth, btnHeight,
		&this->font, "SETTINGS",
		sf::Color(0, 0, 0, 255), sf::Color(100, 100, 100, 255), sf::Color(255, 0, 0, 255));

	this->buttons["EXIT_STATE"] = new Button(
		centerX, centerY + 3*btnHeight, btnWidth, btnHeight,
		&this->font, "EXIT",
		sf::Color(0, 0, 0, 255), sf::Color(100, 100, 100, 255), sf::Color(255, 0, 0, 255));

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys, std::stack<State*>* states)
	: State(window, suppKeys, states) {

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();

	//this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->bg.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {

	for (auto &it : this->buttons) {
		delete it.second;
	}

}

void MainMenuState::updateInput(const float& dt) {

}

void MainMenuState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->endState();
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

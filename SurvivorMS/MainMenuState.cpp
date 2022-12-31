#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables() {

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

void MainMenuState::initGui() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;


	// BG
	this->bg.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg.png")) {
		throw "BG LOAD ERROR";
	}

	this->bg.setTexture(&this->bgTexture);


	// BTNS
	float btnWidth = gui::p2pX(18.75f, vm);
	float btnHeight = gui::p2pY(8.33f, vm);
	unsigned fontSize = gui::calcCharSize(vm);
	float centerX = this->window->getSize().x / 2.f - btnWidth / 2.f;
	float centerY = this->window->getSize().y / 2.f - btnHeight / 2.f;

	float spaceYMultip = 1.25f;

	short btnCount = 0;

	this->buttons["CONTINUE_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight, 
		btnWidth, btnHeight,
		&this->font, "CONTINUE", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));
	btnCount++;
	
	/*this->buttons["SETTINGS_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight, 
		btnWidth, btnHeight,
		&this->font, "SETTINGS", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));*/
	this->buttons["GAME_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight,
		btnWidth, btnHeight,
		&this->font, "NEW GAME", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));
	btnCount++;

	this->buttons["EDITOR_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight, 
		btnWidth, btnHeight,
		&this->font, "EDITOR", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));
	btnCount++;

	this->buttons["EXIT_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight, 
		btnWidth, btnHeight,
		&this->font, "EXIT", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));
	btnCount++;

}

void MainMenuState::resetGui() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

	this->buttons.clear();

	this->initGui();
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initFonts();
	this->initKeyBinds();
	this->initGui();
	this->resetGui();

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
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["CONTINUE_STATE"]->isPressed()) {
		this->states->push(new GameMenu(this->stateData, false));
	}

	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->states->push(new GameState(this->stateData));
		//this->states->push(new GameMenu(this->stateData, true));
	}

	/*if (this->buttons["SETTINGS_STATE"]->isPressed()) {
		this->states->push(new SettingsState(this->stateData));
	}*/

	if (this->buttons["EDITOR_STATE"]->isPressed()) {
		this->states->push(new EditorState(this->stateData));
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

void MainMenuState::renderButtons(sf::RenderTarget& target) {
	//this->testBtn->render(target);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->draw(this->bg);

	this->renderButtons(*target);
}

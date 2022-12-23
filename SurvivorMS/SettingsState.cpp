#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables() {
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground() {

	this->bg.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg.png")) {
		throw "BG LOAD ERROR";
	}

	this->bg.setTexture(&this->bgTexture);
}

void SettingsState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

void SettingsState::initKeyBinds() {

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

void SettingsState::initGui() {
	float btnWidth = 240.f;
	float btnHeight = 60.f;
	unsigned fontSize = 30;
	float centerX = this->window->getSize().x / 2.f - btnWidth / 2.f;
	float centerY = this->window->getSize().y / 2.f - btnHeight / 2.f;

	float spaceYMultip = 1.25f;

	this->buttons["BACK"] = new gui::Button(
		centerX - btnWidth / 1.8f, centerY + 4 * spaceYMultip * btnHeight,
		btnWidth, btnHeight,
		&this->font, "BACK", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));

	this->buttons["APPLY"] = new gui::Button(
		centerX + btnWidth / 1.8f, centerY + 4 * spaceYMultip * btnHeight,
		btnWidth, btnHeight,
		&this->font, "APPLY", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));

	std::vector<std::string> modesStr;
	
	for (auto& it : this->modes) {
		modesStr.push_back(std::to_string(it.width) + 'x' + std::to_string(it.height));
	}

	float listWidth = 160.f, listHeight = 40.f;
	float centerListX = this->window->getSize().x / 2.f - listWidth / 2.f;
	float centerListY = this->window->getSize().y / 2.f - listHeight / 2.f;

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(centerListX + listWidth / 1.8f, centerListY, listWidth, listHeight, this->font, modesStr.data(), modesStr.size());
}

void SettingsState::initText() {

	float centerX = this->window->getSize().x / 2.f - 160.f / 2.f;
	float centerY = this->window->getSize().y / 2.f - 40.f / 2.f;

	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(centerX - 160.f / 1.8f, centerY + 4.f));
	this->optionsText.setCharacterSize(24);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 255));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);

}

SettingsState::SettingsState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState() {

	for (auto& it : this->buttons) {
		delete it.second;
	}
	for (auto& it2 : this->dropDownLists) {
		delete it2.second;
	}
}

void SettingsState::updateInput(const float& dt) {

	if (this->buttons["BACK"]->isPressed()) {
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed()) {
		//this->endState();

		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementID()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

}

void SettingsState::updateGui(const float& dt) {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	for (auto& it : this->dropDownLists) {
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update(const float& dt) {

	this->updateMousePos();

	this->updateInput(dt);

	this->updateGui(dt);

}

void SettingsState::renderGui(sf::RenderTarget& target) {
	//this->testBtn->render(target);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->draw(this->bg);

	this->renderGui(*target);

	target->draw(this->optionsText);
}

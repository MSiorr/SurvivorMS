#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables() {
	this->modes = sf::VideoMode::getFullscreenModes();
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


	// DROP DOWN LIST
	std::vector<std::string> modesStr;
	
	for (auto& it : this->modes) {
		modesStr.push_back(std::to_string(it.width) + 'x' + std::to_string(it.height));
	}

	float listWidth = gui::p2pX(12.5f, vm), listHeight = gui::p2pY(5.55f, vm);
	float centerListX = this->window->getSize().x / 2.f - listWidth / 2.f;
	float centerListY = this->window->getSize().y / 2.f - listHeight / 2.f;
	float listFontSize = gui::calcCharSize(vm) * 0.4f;

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(centerListX + listWidth / 1.8f, centerListY, listWidth, listHeight, listFontSize, this->font, modesStr.data(), static_cast<unsigned>(modesStr.size()));


	// OPTIONS TXT
	float centerTxTX = this->window->getSize().x / 2.f - gui::p2pX(12.5f, vm) / 2.f;
	float centerTxtY = this->window->getSize().y / 2.f - gui::p2pY(5.55f, vm) / 2.f;

	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(centerTxTX - gui::p2pX(12.5f, vm) / 1.8f, centerTxtY + 4.f));
	this->optionsText.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 0.8));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 255));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
	);

}

void SettingsState::resetGui() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

	for (auto& it2 : this->dropDownLists) {
		delete it2.second;
	}

	this->buttons.clear();
	this->dropDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initFonts();
	this->initKeyBinds();
	this->initGui();
	this->resetGui();
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
	
		this->resetGui();
	}

	/*for (auto& it : this->dropDownLists) {
		it.second->update(this->mousePosWindow, dt);
	}*/

}

void SettingsState::updateGui(const float& dt) {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}

	for (auto& it : this->dropDownLists) {
		it.second->update(this->mousePosWindow, dt);
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

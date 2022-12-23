#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables() {

}

void EditorState::initBackground() {

}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN EDITOR STATE");
	}
}

void EditorState::initKeyBinds() {

	std::ifstream ifs("Config/editorStateKeyBinds.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void EditorState::initPauseMenu() {
	this->pMenu = new PauseMenu(*window, this->font);

	this->pMenu->addButton("QUIT", 100.f, "QUIT");
}

void EditorState::initButtons() {


}

void EditorState::initGui() {

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);
}

void EditorState::initTileMap() {

	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);

}

EditorState::EditorState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTileMap();

	//this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->bg.setFillColor(sf::Color::Blue);
}

EditorState::~EditorState() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

	delete this->pMenu;

	delete this->tileMap;

}

void EditorState::updateInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

void EditorState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}
}

void EditorState::updateGui() {
	this->selectorRect.setPosition(
		this->mousePosGrid.x * this->stateData->gridSize, 
		this->mousePosGrid.y * this->stateData->gridSize
	);
}

void EditorState::updatePauseMenuButtons() {

	if (this->pMenu->isButtonPressed("QUIT")) {
		this->endState();
	}
}

void EditorState::update(const float& dt) {

	this->updateMousePos();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) {

		this->updateButtons();
		this->updateGui();

	} else {

		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void EditorState::renderButtons(sf::RenderTarget& target) {
	//this->testBtn->render(target);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target) {
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->renderButtons(*target);
	this->renderGui(*target);

	this->tileMap->render(*target);

	if (this->paused)
		this->pMenu->render(*target);
}

#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables() {

	this->cameraSpeed = 400.f;
}

void EditorState::initEditorStateData() {

	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keyBinds = &this->keyBinds;

	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;

}

void EditorState::initView() {

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
	));

	this->view.setCenter(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f
	);
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

	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pMenu = new PauseMenu(vm, this->font);

	/*this->pMenu->addButton("SAVE", -50.f, "SAVE");
	this->pMenu->addButton("LOAD", 25.f, "LOAD");
	this->pMenu->addButton("QUIT", 100.f, "QUIT");*/

	this->pMenu->addButton(
		"SAVE",
		-gui::p2pY(6.94f, vm),
		gui::p2pX(18.75f, vm),
		gui::p2pY(8.33f, vm),
		gui::calcCharSize(vm),
		"SAVE"
	);

	this->pMenu->addButton(
		"LOAD",
		gui::p2pY(3.47f, vm),
		gui::p2pX(18.75f, vm),
		gui::p2pY(8.33f, vm),
		gui::calcCharSize(vm),
		"LOAD"
	);

	this->pMenu->addButton(
		"QUIT",
		gui::p2pY(13.8f, vm),
		gui::p2pX(18.75f, vm),
		gui::p2pY(8.33f, vm),
		gui::calcCharSize(vm),
		"QUIT"
	);
}

void EditorState::initButtons() {


}

void EditorState::initGui() {



}

void EditorState::initModes() {

	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

void EditorState::initTileMap() {

	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");

}

EditorState::EditorState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeyBinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

	this->initModes();

	//this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->bg.setFillColor(sf::Color::Blue);
}

EditorState::~EditorState() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

	delete this->pMenu;

	delete this->tileMap;

	for (auto& it : this->modes) {
		delete it;
	}

}

void EditorState::updateInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}

}

void EditorState::updateEditorCameraInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_UP")))) {
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_DOWN")))) {
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_LEFT")))) {
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_RIGHT")))) {
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MODE_UP")))) {
		if (this->activeMode < this->modes.size() - 1) {
			this->activeMode++;
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MODE_DOWN")))) {
		if (this->activeMode > 0) {
			this->activeMode--;
		}
	}

}

void EditorState::updateEditorInput(const float& dt) {

	

}

void EditorState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt) {

	

}

void EditorState::updatePauseMenuButtons() {

	if (this->pMenu->isButtonPressed("QUIT")) {
		this->endState();
	}

	if (this->pMenu->isButtonPressed("SAVE")) {
		this->tileMap->saveToFile("text.slmp");
	}

	if (this->pMenu->isButtonPressed("LOAD")) {
		this->tileMap->loadFromFile("text.slmp");
	}
}

void EditorState::updateModes(const float& dt) {

	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt) {

	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) {

		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorCameraInput(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);


	} else {

		this->pMenu->update(this->mousePosWindow);
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

	
}

void EditorState::renderModes(sf::RenderTarget& target) {

	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, sf::Vector2f(0,0), true);

	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);
	this->renderModes(*target);


	if (this->paused) {
		
		target->setView(this->window->getDefaultView());
		this->pMenu->render(*target);
	}

}

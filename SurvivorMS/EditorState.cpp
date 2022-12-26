#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables() {

	this->textureRect = sf::IntRect(
		0, 0, 
		static_cast<int>(this->stateData->gridSize), 
		static_cast<int>(this->stateData->gridSize)
	);

	this->collision = false;
	this->type = TileTypes::DEFAULT;

	this->cameraSpeed = 200.f;
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

void EditorState::initBackground() {

}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN EDITOR STATE");
	}
}

void EditorState::initText() {

	this->cursorTxt.setFont(this->font);
	this->cursorTxt.setCharacterSize(12);
	this->cursorTxt.setFillColor(sf::Color::White);
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

	this->pMenu->addButton("SAVE", -50.f, "SAVE");
	this->pMenu->addButton("LOAD", 25.f, "LOAD");
	this->pMenu->addButton("QUIT", 100.f, "QUIT");
}

void EditorState::initButtons() {


}

void EditorState::initGui() {

	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineThickness(1.f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255,255,255,150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 800.f, 200.f, 
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "TS");


}

void EditorState::initTileMap() {

	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");

}

EditorState::EditorState(StateData* stateData)
	: State(stateData) {

	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeyBinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

	//this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->bg.setFillColor(sf::Color::Blue);
}

EditorState::~EditorState() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

	delete this->pMenu;

	delete this->tileMap;

	delete this->textureSelector;

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

}

void EditorState::updateEditorInput(const float& dt) {

	


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) { 
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // NO KEYTIME

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {

			if (!this->textureSelector->getActive()) {
		
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);	
			} else {

				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {

			if (!this->textureSelector->getActive()) {

				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			} else {

			}
		}

		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_COLLISION"))) && this->getKeytime()) {

		this->collision = !this->collision;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPE_INC"))) && this->getKeytime()) {

		++this->type;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPE_DEC"))) && this->getKeytime()) {

		this->type = std::max(0, this->type-1);
	}

}

void EditorState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt) {

	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive()) {

		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(
			this->mousePosGrid.x * this->stateData->gridSize, 
			this->mousePosGrid.y * this->stateData->gridSize
		);
	}


	this->cursorTxt.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y - 50.f);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type;

	this->cursorTxt.setString(ss.str());

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

void EditorState::update(const float& dt) {

	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) {

		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorCameraInput(dt);
		this->updateEditorInput(dt);

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

	if (!this->textureSelector->getActive()) {

		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorTxt);
}

void EditorState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) {
		
		target->setView(this->window->getDefaultView());
		this->pMenu->render(*target);
	}

}

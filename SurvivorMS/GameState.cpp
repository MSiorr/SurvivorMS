#include "stdafx.h"
#include "GameState.h"

void GameState::initView() {

	this->view.setSize(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));

	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f
	));
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

void GameState::initKeyBinds() {

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

void GameState::initTextures() {

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/playerSheet.png")) {
		throw "PLAYER TEXTURE ERROR";
	}

}

void GameState::initPauseMenu() {
	this->pMenu = new PauseMenu(*window, this->font);

	this->pMenu->addButton("QUIT", 100.f, "QUIT");
}

void GameState::initPlayer() {
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {

	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("text.slmp");
}

GameState::GameState(StateData* stateData)
	: State(stateData) {

	this->initView();
	this->initFonts();
	this->initKeyBinds();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayer();
	this->initTileMap();
}

GameState::~GameState() {
	delete this->pMenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float& dt) {

	this->view.setCenter(this->player->getPosition());
}

void GameState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player->move(0.f, 1.f, dt);
	}
}

void GameState::updatePauseMenuButtons() {
	if (this->pMenu->isButtonPressed("QUIT") && this->getKeytime()) {
		this->endState();
	}
}


void GameState::update(const float& dt) {

	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) {

		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->player->update(dt);
	} else {

		this->pMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}


}

void GameState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target);

	this->player->render(*target);

	if (this->paused) {
		target->setView(this->window->getDefaultView());
		this->pMenu->render(*target);
	}
}
#include "stdafx.h"
#include "GameState.h"

void GameState::initDefferedRender() {

	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0, 0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));

}

void GameState::initView() {

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
	));

	this->view.setCenter(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
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
	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	
	this->pMenu = new PauseMenu(vm, this->font);

	this->pMenu->addButton(
		"QUIT", 
		gui::p2pY(13.8f, vm),
		gui::p2pX(18.75f, vm), 
		gui::p2pY(8.33f, vm), 
		gui::calcCharSize(vm),
		"QUIT"
	);
}

void GameState::initShaders() {

	if(!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")){
		
		std::cout << "ERROR WITH SHADERS" << "\n";
	}
}

void GameState::initPlayer() {
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI() {

	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap() {

	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("text.slmp");
}

GameState::GameState(StateData* stateData)
	: State(stateData) {

	this->initDefferedRender();
	this->initView();
	this->initFonts();
	this->initKeyBinds();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initPlayer();
	this->initPlayerGUI();
	this->initTileMap();
}

GameState::~GameState() {
	delete this->pMenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
}

void GameState::updateView(const float& dt) {

	this->view.setCenter(
		std::floor((this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 5.f) * 100.f) / 100.f,
		std::floor((this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 5.f) * 100.f) / 100.f
	);
}

void GameState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerGUI(const float& dt) {

	this->playerGUI->update(dt);
}

void GameState::updateTileMap(const float& dt) {

	this->tileMap->update(dt);
	this->tileMap->updateCollision(this->player, dt);
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
		if (this->getKeytime()) {

			this->player->gainHP(1);
			this->player->gainExp(100);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player->move(0.f, 1.f, dt);
		if (this->getKeytime()) {

			this->player->loseHP(1);
			this->player->loseExp(100);
		}
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

		this->updateTileMap(dt);
		this->player->update(dt);

		this->playerGUI->update(dt);

	} else {

		this->pMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}


}

void GameState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, 
		this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)), 
		&this->coreShader, 
		this->player->getCenter()
	);

	this->player->render(this->renderTexture, &this->coreShader, true);

	this->tileMap->renderDeferred(
		this->renderTexture, 
		&this->coreShader,
		this->player->getCenter()
	);


	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) {
		

		this->pMenu->render(this->renderTexture);
	}

	//FINAL 

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);



	//target->setView(this->view);
	//this->tileMap->render(*target);

	//this->player->render(*target);

	//if (this->paused) {
	//	target->setView(this->window->getDefaultView());
	//	this->pMenu->render(*target);
	//}
}
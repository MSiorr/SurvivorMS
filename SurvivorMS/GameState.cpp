#include "stdafx.h"
#include "GameState.h"

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

	//this->keyBinds.emplace(KEYACTIONS::MOVE_LEFT, supportedKeys->at(SUPPKEYS::A));
	//this->keyBinds.emplace(KEYACTIONS::MOVE_RIGHT, supportedKeys->at(SUPPKEYS::D));
	//this->keyBinds.emplace(KEYACTIONS::MOVE_UP, supportedKeys->at(SUPPKEYS::W));
	//this->keyBinds.emplace(KEYACTIONS::MOVE_DOWN, supportedKeys->at(SUPPKEYS::S));
	//this->keyBinds.emplace(KEYACTIONS::CLOSE, supportedKeys->at(SUPPKEYS::ESC));
}

void GameState::initTextures() {

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/playerSheet.png")) {
		throw "PLAYER TEXTURE ERROR";
	}

}

void GameState::initPlayer() {
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys, std::stack<State*>* states)
	: State(window, suppKeys, states) {

	this->initKeyBinds();
	this->initTextures();
	this->initPlayer();
}

GameState::~GameState() {
	delete this->player;
}

void GameState::updateInput(const float& dt) {

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
		this->endState();
	}
}

void GameState::update(const float& dt) {

	this->updateMousePos();
	this->updateInput(dt);

	this->player->update(dt);

}

void GameState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->player->render(target);
}
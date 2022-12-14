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

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys)
	: State(window, suppKeys) {

	this->initKeyBinds();
}

GameState::~GameState() {
}


void GameState::endState() {

	std::cout << "BYE BYE " << "\n";
}

void GameState::updateInput(const float& dt) {
	this->checkQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
		this->player.move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
		this->player.move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
		this->player.move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player.move(dt, 0.f, 1.f);
	}
}

void GameState::update(const float& dt) {

	this->updateInput(dt);

	this->player.update(dt);

}

void GameState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->player.render(target);
}
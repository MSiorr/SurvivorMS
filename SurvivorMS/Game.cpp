#include "stdafx.h"
#include "Game.h"



// Private
void Game::initVariables() {

	this->window = nullptr;
	this->dt = 0.f;

	this->gridSize = 100.f;
}

void Game::initGraphicsSettings() {

	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData() {

	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.suppKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initWindow() {

	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title,
			sf::Style::Fullscreen, 
			this->gfxSettings.contextSettings
		);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, 
			this->gfxSettings.contextSettings
		);
	
	//this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(this->gfxSettings.maxFps);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys() {

	std::ifstream ifs("Config/supportedKeys.ini");

	if (ifs.is_open()) {
		std::string key;
		int val;

		while (ifs >> key >> val) {
			this->supportedKeys[key] = val;
		}
	}

	ifs.close();

	//this->supportedKeys.emplace(SUPPKEYS::W, sf::Keyboard::Key::W);
	//this->supportedKeys.emplace(SUPPKEYS::A, sf::Keyboard::Key::A);
	//this->supportedKeys.emplace(SUPPKEYS::S, sf::Keyboard::Key::S);
	//this->supportedKeys.emplace(SUPPKEYS::D, sf::Keyboard::Key::D);
	//this->supportedKeys.emplace(SUPPKEYS::ESC, sf::Keyboard::Key::Escape);
}

void Game::initStates() {

	this->states.push(new MainMenuState(&this->stateData));
	//this->states.push(new GameState(this->window, &this->supportedKeys));

}

// Cons/Decons
Game::Game() {

	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();

}

Game::~Game() {

	delete this->window;

	if (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApp() {
	std::cout << "APP END" << "\n";
}

void Game::updateDt() {

	this->dt = dtTime.restart().asSeconds();

}

// Public
void Game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				//this->window->close();
			break;
		}
	}
}

void Game::update() {

	this->pollEvents();

	if (!this->states.empty()) {
		if (this->window->hasFocus()) {

			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit()) {

				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	} else {
		this->endApp();
		this->window->close();
	}


}

void Game::render() {

	this->window->clear();

	// Game items
	if (!this->states.empty()) {
		this->states.top()->render();
	}

	this->window->display();
}

void Game::run() {

	while (this->window->isOpen()) {

		this->updateDt();
		this->update();
		this->render();
	}

}

#include "stdafx.h"
#include "Game.h"



// Private
void Game::initVariables() {

	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow() {

	// Take window data from window.ini
	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "SURVIVOR.MS";
	sf::VideoMode window_size = sf::VideoMode::getDesktopMode();
	unsigned int fps = 144;
	bool vsyncEnabled = false;
	bool fullscreen = false;
	unsigned antialiasing_lvl = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_size.width >> window_size.height;
		ifs >> fps;
		ifs >> vsyncEnabled;
		ifs >> fullscreen;
		ifs >> antialiasing_lvl;
	}

	ifs.close();

	this->fullscreen = fullscreen;

	this->windowSettings.antialiasingLevel = antialiasing_lvl;

	if(fullscreen)
		this->window = new sf::RenderWindow(window_size, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	
	//this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(fps);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
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

	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
	//this->states.push(new GameState(this->window, &this->supportedKeys));

}

// Cons/Decons
Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initKeys();
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
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {

			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
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

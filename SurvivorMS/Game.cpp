#include "stdafx.h"
#include "Game.h"

// Private
void Game::initVariables() {

	this->window = nullptr;
}

void Game::initWindow() {

	// Take window data from window.ini
	std::ifstream ifs("Config/window.ini");

	std::string title = "SURVIVOR.MS";
	sf::VideoMode window_size(1600, 900);
	unsigned int fps = 144;
	bool vsyncEnabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_size.width >> window_size.height;
		ifs >> fps;
		ifs >> vsyncEnabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(fps);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
}

void Game::initStates() {

	this->states.push(new GameState(this->window));

}

// Cons/Decons
Game::Game() {

	this->initVariables();
	this->initWindow();
}

Game::~Game() {

	delete this->window;

	if (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt() {

	this->dt = dtTime.restart().asSeconds();

	system("cls");
	std::cout << 1 / this->dt << std::endl;

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
				this->window->close();
			break;
		}
	}
}

void Game::update() {

	this->pollEvents();

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
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

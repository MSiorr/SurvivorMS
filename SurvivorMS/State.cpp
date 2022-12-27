#include "stdafx.h"
#include "State.h"

State::State(StateData* stateData) {

	this->stateData = stateData;

	this->window = stateData->window;
	this->supportedKeys = stateData->suppKeys;
	this->states = stateData->states;

	this->quit = false;
	this->paused = false;

	this->keytime = 0.f;
	this->keytimeMax = 160.f;

	this->gridSize = stateData->gridSize;
}

State::~State() {
}

const bool& State::getQuit() const {
	return this->quit;
}

const bool State::getKeytime() {
	
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void State::endState() {
	this->quit = true;
}

void State::pauseState() {
	this->paused = true;
}

void State::unpauseState() {
	this->paused = false;
}

void State::updateMousePos(sf::View* view) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
		static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
	);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt) {
	if (this->keytime < this->keytimeMax)
		this->keytime += 1000.f * dt;
}


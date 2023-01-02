#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver(sf::VideoMode& vm, sf::Font& font, std::stack<State*>* states) : font(font) {

	this->states = states;

	this->gameOverTxt.setFont(this->font);
	this->gameOverTxt.setString("GAME OVER");
	this->gameOverTxt.setFillColor(sf::Color(200, 50, 50, 200));
	this->gameOverTxt.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 2));
	this->gameOverTxt.setPosition(
		vm.width / 2 - this->gameOverTxt.getGlobalBounds().width / 2,
		vm.height / 2 - this->gameOverTxt.getGlobalBounds().height / 2
	);

	this->infoTxt.setFont(this->font);
	this->infoTxt.setString("Press 'Space' to continue");
	this->infoTxt.setFillColor(sf::Color(200, 200, 200, 200));
	this->infoTxt.setCharacterSize(gui::calcCharSize(vm));
	this->infoTxt.setPosition(
		vm.width / 2 - this->infoTxt.getGlobalBounds().width / 2,
		vm.height / 2 - this->infoTxt.getGlobalBounds().height / 2 + vm.height / 4
	);

	this->bg.setFillColor(sf::Color(20, 20, 20, 200));
	this->bg.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));
}

GameOver::~GameOver() {
}

void GameOver::update(const sf::Vector2i& mousePosWindow) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		this->states->top()->endState();
	}
}

void GameOver::render(sf::RenderTarget& target) {

	target.draw(this->bg);
	target.draw(this->gameOverTxt);
	target.draw(this->infoTxt);
}

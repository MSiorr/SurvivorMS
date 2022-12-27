#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont() {

	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN PLAYER GUI");
	}
}

void PlayerGUI::initHPBar() {

	float width = gui::p2pX(26.875f, vm);
	float height = gui::p2pY(4.44f, vm);
	float x = gui::p2pX(1.56f, vm);
	float y = gui::p2pY(1.56f, vm);

	this->hpBar = new gui::ProgressBar(
		1.56f, 1.56f,
		26.875f, 4.44f,
		0.6f,
		this->player->getAttributeComponent()->hpMax,
		this->vm,
		&this->font
	);

	/*this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarIn.setSize(sf::Vector2f(width, height));
	this->hpBarIn.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarIn.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setFillColor(sf::Color::White);
	this->hpBarText.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 0.6));
	this->hpBarText.setPosition(
		this->hpBarIn.getPosition().x + gui::p2pX(0.78f, vm),
		this->hpBarIn.getPosition().y + gui::p2pY(0.694f, vm)
	);*/
}

void PlayerGUI::initExpBar() {

	float width = gui::p2pX(23.437f, vm);
	float height = gui::p2pY(3.333f, vm);
	float x = gui::p2pX(5.f, vm);
	float y = gui::p2pY(8.88f, vm);

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarIn.setSize(sf::Vector2f(width, height));
	this->expBarIn.setFillColor(sf::Color(200, 140, 20, 200));
	this->expBarIn.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setFillColor(sf::Color::White);
	this->expBarText.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 0.466));
	this->expBarText.setPosition(
		this->expBarBack.getPosition().x + gui::p2pX(0.78f, vm),
		this->expBarBack.getPosition().y + gui::p2pY(0.555f, vm)
	);
}

void PlayerGUI::initLevelBar() {

	float width = gui::p2pX(2.34f, vm);
	float height = gui::p2pY(3.333f, vm);
	float x = gui::p2pX(1.56f, vm);
	float y = gui::p2pY(8.88f, vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setFillColor(sf::Color::White);
	this->levelBarText.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 0.533));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.78f, vm),
		this->levelBarBack.getPosition().y + gui::p2pY(0.277f, vm)
	);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm) {

	this->player = player;

	this->initFont();
	this->initHPBar();
	this->initExpBar();
	this->initLevelBar();

}

PlayerGUI::~PlayerGUI() {
}

void PlayerGUI::updateHPBar() {

	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::updateExpBar() {

	float percent =
		static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarIn.setSize(sf::Vector2f(
		static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
		this->expBarIn.getSize().y
	));

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

void PlayerGUI::updateLevelBar() {

	this->levelBarString = std::to_string(this->player->getAttributeComponent()->lvl);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::update(const float& dt) {

	this->updateHPBar();
	this->updateExpBar();
	this->updateLevelBar();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target) {

	this->hpBar->render(target);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target) {

	target.draw(this->expBarBack);
	target.draw(this->expBarIn);
	target.draw(this->expBarText);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target) {

	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::render(sf::RenderTarget& target) {

	this->renderHPBar(target);
	this->renderExpBar(target);
	this->renderLevelBar(target);
}

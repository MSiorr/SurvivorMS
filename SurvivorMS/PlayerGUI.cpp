#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont() {

	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN PLAYER GUI");
	}
}

void PlayerGUI::initHPBar() {

	float width = 344.f;
	float height = 32.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarIn.setSize(sf::Vector2f(width, height));
	this->hpBarIn.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarIn.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setFillColor(sf::Color::White);
	this->hpBarText.setCharacterSize(18);
	this->hpBarText.setPosition(
		this->hpBarIn.getPosition().x + 10.f,
		this->hpBarIn.getPosition().y + 5.f
	);
}

void PlayerGUI::initExpBar() {

	float width = 300.f;
	float height = 24.f;
	float x = 64.f;
	float y = 64.f;

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarIn.setSize(sf::Vector2f(width, height));
	this->expBarIn.setFillColor(sf::Color(200, 140, 20, 200));
	this->expBarIn.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setFillColor(sf::Color::White);
	this->expBarText.setCharacterSize(14);
	this->expBarText.setPosition(
		this->expBarBack.getPosition().x + 10.f,
		this->expBarBack.getPosition().y + 4.f
	);
}

void PlayerGUI::initLevelBar() {

	float width = 30.f;
	float height = 24.f;
	float x = 20.f;
	float y = 64.f;

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setFillColor(sf::Color::White);
	this->levelBarText.setCharacterSize(16);
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + 10.f,
		this->levelBarBack.getPosition().y + 2.f
	);
}

PlayerGUI::PlayerGUI(Player* player) {

	this->player = player;

	this->initFont();
	this->initHPBar();
	this->initExpBar();
	this->initLevelBar();

}

PlayerGUI::~PlayerGUI() {
}

void PlayerGUI::updateHPBar() {

	float percent = 
		static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarIn.setSize(sf::Vector2f(
		static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
		this->hpBarIn.getSize().y
	));

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
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

	target.draw(this->hpBarBack);
	target.draw(this->hpBarIn);
	target.draw(this->hpBarText);
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

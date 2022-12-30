#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont() {

	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN PLAYER GUI");
	}
}

void PlayerGUI::initHPBar() {

	this->hpBar = new gui::ProgressBar(
		1.56f, 1.56f,
		26.875f, 4.44f,
		0.6f,
		this->player->getAttributeComponent()->hpMax, sf::Color(250, 20, 20, 200),
		this->vm,
		&this->font
	);

}

void PlayerGUI::initExpBar() {

	this->expBar = new gui::ProgressBar(
		5.f, 8.88f,
		23.437f, 3.333f,
		0.466f,
		this->player->getAttributeComponent()->expNext, sf::Color(200, 140, 20, 200),
		this->vm,
		&this->font
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

void PlayerGUI::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player) {

	this->playerTabs = new PlayerGUITabs(vm, font, player);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm) {

	this->player = player;

	this->initFont();
	this->initHPBar();
	this->initExpBar();
	this->initLevelBar();
	this->initPlayerTabs(vm, font, *player);

}

PlayerGUI::~PlayerGUI() {

	delete this->hpBar;
	delete this->expBar;
	delete this->playerTabs;
}

const bool PlayerGUI::getTabsOpen() const {
	
	return this->playerTabs->tabsOpen();
}

void PlayerGUI::toggleCharacterTab() {
	this->playerTabs->toggleTab(PLAYER_TABS::CHARACTER_TAB);
}

void PlayerGUI::updateHPBar() {

	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::updateExpBar() {

	this->expBar->updateMaxVal(this->player->getAttributeComponent()->expNext);
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::updateLevelBar() {

	this->levelBarString = std::to_string(this->player->getAttributeComponent()->lvl);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updatePlayerTabs() {

	this->playerTabs->update();
}

void PlayerGUI::update(const float& dt) {

	this->updateHPBar();
	this->updateExpBar();
	this->updateLevelBar();
	this->updatePlayerTabs();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target) {

	this->hpBar->render(target);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target) {

	this->expBar->render(target);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target) {

	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderPlayerTabs(sf::RenderTarget& target) {

	this->playerTabs->render(target);
}

void PlayerGUI::render(sf::RenderTarget& target) {

	this->renderHPBar(target);
	this->renderExpBar(target);
	this->renderLevelBar(target);
	this->renderPlayerTabs(target);

}

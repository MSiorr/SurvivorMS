#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont() {

	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN PLAYER GUI");
	}
}

void PlayerGUI::initExpBar() {

	this->expBar = new gui::ProgressBar(
		1.25f, 2.22f,
		97.5f, 3.333f,
		0.466f,
		this->player->getAttributeComponent()->expNext, sf::Color(116, 225, 39, 200),
		this->vm,
		&this->font,
		false
	);
}

void PlayerGUI::initLevelBar() {

	float width = gui::p2pX(3.6f, this->vm);
	float height = gui::p2pY(5.555f, this->vm);
	float x = gui::p2pX(50.f, this->vm) - width / 2.f;
	float y = gui::p2pY(6.f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 0));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setFillColor(sf::Color::White);
	this->levelBarText.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(this->vm) * 1.6f));
	this->levelBarText.setString("1");
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + (width / 2.f) - (this->levelBarText.getGlobalBounds().width / 1.4f),
		this->levelBarBack.getPosition().y + gui::p2pY(0.25f, this->vm)
	);
}

void PlayerGUI::initGold() {

	if (!this->goldTexture.loadFromFile("Resources/Images/Sprites/coin.png"))
		std::cout << "ERROR GOLD TEXTURE P_GUI" << "\n";

	this->goldIcon.setTexture(&this->goldTexture);
	this->goldIcon.setPosition(
		gui::p2pX(90.f, this->vm),
		gui::p2pY(6.8f, this->vm)
	);
	this->goldIcon.setSize(sf::Vector2f(
		gui::p2pX(2.5f, vm),
		gui::p2pY(4.44f, vm)
	));

	this->goldTxt.setFont(this->font);
	this->goldTxt.setCharacterSize(gui::calcCharSize(this->vm));
	this->goldTxt.setFillColor(sf::Color(222, 222, 222, 222));
	this->goldTxt.setString("1000");
	this->goldTxt.setPosition(
		gui::p2pX(93.f, this->vm),
		gui::p2pY(6.f, this->vm)
	);
}

void PlayerGUI::initKillCounter() {

	if (!this->skullTexture.loadFromFile("Resources/Images/Sprites/skull.png"))
		std::cout << "ERROR GOLD TEXTURE P_GUI" << "\n";

	this->skullIcon.setTexture(&this->skullTexture);
	this->skullIcon.setPosition(
		gui::p2pX(2.f, this->vm),
		gui::p2pY(6.8f, this->vm)
	);
	this->skullIcon.setSize(sf::Vector2f(
		gui::p2pX(2.5f, vm),
		gui::p2pY(4.44f, vm)
	));

	this->killCountTxt.setFont(this->font);
	this->killCountTxt.setCharacterSize(gui::calcCharSize(this->vm));
	this->killCountTxt.setFillColor(sf::Color(222, 222, 222, 222));
	this->killCountTxt.setString("1000");
	this->killCountTxt.setPosition(
		gui::p2pX(5.f, this->vm),
		gui::p2pY(6.f, this->vm)
	);
}

void PlayerGUI::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player) {

	this->playerTabs = new PlayerGUITabs(vm, font, player);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm) : vm(vm) {

	this->player = player;

	this->initFont();
	this->initExpBar();
	this->initLevelBar();
	this->initPlayerTabs(vm, font, *player);
	this->initGold();
	this->initKillCounter();

}

PlayerGUI::~PlayerGUI() {

	delete this->expBar;
	delete this->playerTabs;
}

const bool PlayerGUI::getTabsOpen() const {
	
	return this->playerTabs->tabsOpen();
}

void PlayerGUI::toggleCharacterTab() {
	this->playerTabs->toggleTab(PLAYER_TABS::CHARACTER_TAB);
}

void PlayerGUI::updateExpBar() {

	this->expBar->updateMaxVal(this->player->getAttributeComponent()->expNext);
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::updateLevelBar() {

	this->levelBarString = std::to_string(this->player->getAttributeComponent()->lvl);
	this->levelBarText.setString(this->levelBarString);
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + (this->levelBarBack.getSize().x / 2.f) - (this->levelBarText.getGlobalBounds().width / 1.8f),
		this->levelBarBack.getPosition().y + gui::p2pY(0.25f, this->vm)
	);
}

void PlayerGUI::updatePlayerTabs() {

	this->playerTabs->update();
}

void PlayerGUI::updateGold(const float& gold) {

	std::stringstream ss;
	ss << gold;

	this->goldTxt.setString(ss.str());
}

void PlayerGUI::updateKillCounter(const float& kills) {

	std::stringstream ss;
	ss << kills;

	this->killCountTxt.setString(ss.str());
}

void PlayerGUI::update(const float& dt, const float& gold, const float& kills) {

	this->updateExpBar();
	this->updateLevelBar();
	this->updatePlayerTabs();
	this->updateGold(gold);
	this->updateKillCounter(kills);
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

void PlayerGUI::renderGold(sf::RenderTarget& target) {

	target.draw(this->goldIcon);
	target.draw(this->goldTxt);
}

void PlayerGUI::renderKillCounter(sf::RenderTarget& target) {

	target.draw(this->skullIcon);
	target.draw(this->killCountTxt);
}

void PlayerGUI::render(sf::RenderTarget& target) {

	this->renderExpBar(target);
	this->renderLevelBar(target);
	this->renderPlayerTabs(target);
	this->renderGold(target);
	this->renderKillCounter(target);
}

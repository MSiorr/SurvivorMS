#include "stdafx.h"
#include "GameMenu.h"

void GameMenu::initFonts() {

	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

void GameMenu::initPlayerData(bool newGame) {

	this->playerData = new PlayerData(newGame);
}

void GameMenu::initKeyBinds() {
}

void GameMenu::initGuiItems() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	float btnWidth = gui::p2pX(7.88f, vm); // 100px
	float btnHeight = gui::p2pY(13.88f, vm); // 100px

	float leftX = gui::p2pX(3.5f, vm); // 20px
	float rightX = gui::p2pX(34.8f, vm);
	float columnY = this->mainTopPadding;

	float ySpace = gui::p2pY(2.f, vm);

	int rowCount = 0;

	this->buttons["WEAPON_ITEM"] = new gui::Button(
		leftX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/weapon.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255,255,255,160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);

	this->buttons["CHESTPLATE_ITEM"] = new gui::Button(
		rightX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/chestplate.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255, 255, 255, 160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);

	rowCount++;

	this->buttons["NECKLACE_ITEM"] = new gui::Button(
		leftX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/necklace.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255, 255, 255, 160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);

	this->buttons["BELT_ITEM"] = new gui::Button(
		rightX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/belt.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255, 255, 255, 160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);

	rowCount++;

	this->buttons["GLOVES_ITEM"] = new gui::Button(
		leftX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/gloves.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255, 255, 255, 160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);

	this->buttons["BOOTS_ITEM"] = new gui::Button(
		rightX, columnY + rowCount * (btnHeight + ySpace),
		btnWidth, btnHeight,
		&this->font, "Resources/Images/GameMenu/boots.png", 0,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(255, 255, 255, 160), sf::Color(255, 255, 255, 255), sf::Color::White,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, true
	);
}

void GameMenu::initGui() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//BG
	this->bg.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/gameMenu.png")) {
		throw "BG LOAD ERROR";
	}

	this->bg.setTexture(&this->bgTexture);

	this->dmgTxt.setFont(this->font);
	this->dmgTxt.setString(this->playerData->getDMGString());
	this->dmgTxt.setFillColor(sf::Color::White);
	this->dmgTxt.setCharacterSize(gui::calcCharSize(vm));
	this->dmgTxt.setPosition(
		gui::p2pX(3.5f, vm),
		gui::p2pY(72.f, vm)
	);

	this->hpTxt.setFont(this->font);
	this->hpTxt.setString(this->playerData->getHPString());
	this->hpTxt.setFillColor(sf::Color::White);
	this->hpTxt.setCharacterSize(gui::calcCharSize(vm));
	this->hpTxt.setPosition(
		gui::p2pX(34.8f, vm),
		gui::p2pY(72.f, vm)
	);


	// BTNS
	float btnWidth = gui::p2pX(20.f, vm);
	float btnHeight = gui::p2pY(6.f, vm);
	unsigned fontSize = static_cast<unsigned>(gui::calcCharSize(vm) * 0.8f);
	float centerX = this->window->getSize().x / 2.f;
	float centerY = this->window->getSize().y / 2.f;

	this->buttons["BACK_STATE"] = new gui::Button(
		gui::p2pX(1.5f, vm), gui::p2pY(4.f, vm),
		btnWidth / 2.f, btnHeight,
		&this->font, "< BACK", fontSize,
		sf::Color(140, 140, 140, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50)
	);

	this->buttons["PLAY_NORMAL"] = new gui::Button(
		centerX - (btnWidth * 1.1f), gui::p2pY(80.f, vm),
		btnWidth, btnHeight * 1.6f,
		&this->font, "PLAY NORMAL", static_cast<unsigned>(fontSize * 1.5f),
		sf::Color(140, 140, 140, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50)
	);

	this->buttons["PLAY_EDITOR"] = new gui::Button(
		centerX + (btnWidth * 0.1f), gui::p2pY(80.f, vm),
		btnWidth, btnHeight * 1.6f,
		&this->font, "PLAY EDITOR", static_cast<unsigned>(fontSize * 1.5f),
		sf::Color(140, 140, 140, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50)
	);

	/*this->buttons["EXIT_STATE"] = new gui::Button(
		centerX, centerY + btnCount * spaceYMultip * btnHeight,
		btnWidth, btnHeight,
		&this->font, "EXIT", fontSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 140), sf::Color(0, 0, 0, 50));*/
}

void GameMenu::initPlayerAvatar() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	if (!this->playerAvTexture.loadFromFile("Resources/Images/Sprites/playerSheet.png")) {
		throw "PLAYER TEXTURE ERROR IN GAME MENU";
	}

	this->playerAvAnimComp = new AnimationComponent(this->playerAv, this->playerAvTexture);
	this->playerAvAnimComp->addAnim("AV_IDLE", 16.f, 0, 0, 3, 0, 46, 64);

	this->playerAv.setPosition(
		gui::p2pX(15.75f, vm),
		this->mainTopPadding + gui::p2pY(10.09f, vm)
	);

	float scale = static_cast<float>(vm.width) * 0.1468f / 46.f;

	this->playerAv.setScale(scale, scale);
}

void GameMenu::initInfoBox() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buyActive = false;
	this->activeItem = EQTYPES::WEAPON;

	this->infoBox.setFillColor(sf::Color(0, 0, 0, 50));
	this->infoBox.setSize(sf::Vector2f(
		gui::p2pX(40.f, vm),
		gui::p2pY(45.64f, vm)
	));
	this->infoBox.setPosition(
		gui::p2pX(55.f, vm),
		this->mainTopPadding
	);

	float posX = this->infoBox.getPosition().x + gui::p2pX(1.5f, vm);

	this->headerTxt.setFont(this->font);
	this->headerTxt.setString(this->playerData->getItemName(this->activeItem));
	this->headerTxt.setFillColor(sf::Color::White);
	this->headerTxt.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * 1.33f));
	this->headerTxt.setPosition(
		posX,
		this->infoBox.getPosition().y + gui::p2pY(2.77f, vm)
	);

	this->infoTxt.setFont(this->font);
	this->infoTxt.setString(this->playerData->getItemInfo(this->activeItem));
	this->infoTxt.setFillColor(sf::Color::White);
	this->infoTxt.setCharacterSize(gui::calcCharSize(vm));
	this->infoTxt.setPosition(
		posX,
		this->infoBox.getPosition().y + gui::p2pY(15.f, vm)
	);

	this->goldShapeBox.setPosition(
		posX,
		this->infoBox.getPosition().y + gui::p2pY(30.f, vm)
	);
	this->goldShapeBox.setSize(sf::Vector2f(
		gui::p2pX(2.5f, vm),
		gui::p2pY(4.44f, vm)
	));

	this->costTxt.setFont(this->font);
	this->costTxt.setString(this->playerData->getItemCostString(this->activeItem));
	this->costTxt.setFillColor(this->playerData->canLvlUp(this->activeItem) ? sf::Color::Green : sf::Color::Red);
	this->costTxt.setCharacterSize(30);
	this->costTxt.setPosition(
		posX + gui::p2pX(3.f, vm),
		this->infoBox.getPosition().y + gui::p2pY(29.5f, vm)
	);


	this->buttons["BUY"] = new gui::Button(
		posX, this->infoBox.getPosition().y + gui::p2pY(36.f, vm),
		gui::p2pX(10.f, vm), gui::p2pY(6.f, vm),
		&this->font, "LVL UP", static_cast<unsigned>(gui::calcCharSize(vm) * 0.84f),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 50),
		sf::Color(50, 200, 50, 200), sf::Color(50, 200, 50, 255), sf::Color(50, 200, 50, 100)
	);

}

void GameMenu::initGold() {

	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->goldTxt.setFont(this->font);
	this->goldTxt.setString(this->playerData->getGoldString());
	this->goldTxt.setFillColor(sf::Color::White);
	this->goldTxt.setCharacterSize(gui::calcCharSize(vm));
	this->goldTxt.setPosition(
		gui::p2pX(86.f, vm),
		gui::p2pY(4.f, vm)
	);

	if (!this->goldTexture.loadFromFile("Resources/Images/Sprites/coin.png")) {
		std::cout << "ERROR GOLD TEXTURE" << "\n";
	}

	this->goldShapeTop.setTexture(&this->goldTexture);
	this->goldShapeBox.setTexture(&this->goldTexture);

	this->goldShapeTop.setPosition(
		gui::p2pX(83.f, vm),
		gui::p2pY(4.5f, vm)
	);
	this->goldShapeTop.setSize(sf::Vector2f(
		gui::p2pX(2.5f, vm),
		gui::p2pY(4.44f, vm)
	));
}

GameMenu::GameMenu(StateData* stateData, bool newGame) : State(stateData) {

	this->mainTopPadding = gui::p2pY(24.f, this->stateData->gfxSettings->resolution);
	this->backFromGame = false;

	this->initFonts();
	this->initPlayerData(newGame);
	this->initGold();
	this->initKeyBinds();
	this->initGuiItems();
	this->initGui();
	this->initPlayerAvatar();
	this->initInfoBox();
}

GameMenu::~GameMenu() {
}

void GameMenu::resetGUI() {

	this->headerTxt.setString(this->playerData->getItemName(this->activeItem));
	this->infoTxt.setString(this->playerData->getItemInfo(this->activeItem));
	this->costTxt.setString(this->playerData->getItemCostString(this->activeItem));
	this->costTxt.setFillColor(this->playerData->canLvlUp(this->activeItem) ? sf::Color::Green : sf::Color::Red);
	this->goldTxt.setString(this->playerData->getGoldString());
	this->hpTxt.setString(this->playerData->getHPString());
	this->dmgTxt.setString(this->playerData->getDMGString());

}

void GameMenu::changeActiveItem(short key) {

	this->activeItem = key;
	this->resetGUI();
}

void GameMenu::updateInput(const float& dt) {
}

void GameMenu::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}

	if (this->buttons["BACK_STATE"]->isPressed() && this->getKeytime()) {
		this->states->pop();
	}

	if (this->buttons["WEAPON_ITEM"]->isPressed() && this->getKeytime()) {

		this->changeActiveItem(EQTYPES::WEAPON);
	}

	if (this->buttons["CHESTPLATE_ITEM"]->isPressed() && this->getKeytime()) {
		
		this->changeActiveItem(EQTYPES::CHESTPLATE);
	}

	if (this->buttons["NECKLACE_ITEM"]->isPressed() && this->getKeytime()) {
		
		this->changeActiveItem(EQTYPES::NECKLACE);
	}

	if (this->buttons["BELT_ITEM"]->isPressed() && this->getKeytime()) {
		
		this->changeActiveItem(EQTYPES::BELT);
	}

	if (this->buttons["GLOVES_ITEM"]->isPressed() && this->getKeytime()) {
		
		this->changeActiveItem(EQTYPES::GLOVES);
	}

	if (this->buttons["BOOTS_ITEM"]->isPressed() && this->getKeytime()) {
		
		this->changeActiveItem(EQTYPES::BOOTS);
	}

	if (this->buttons["BUY"]->isPressed() && this->getKeytime()) {

		this->playerData->lvlUp(this->activeItem);
		this->resetGUI();
	}

	if (this->buttons["PLAY_NORMAL"]->isPressed() && this->getKeytime()) {

		this->backFromGame = true;
		this->states->push(new GameState(this->stateData, this->playerData, "map1.txt"));
	}

	if (this->buttons["PLAY_EDITOR"]->isPressed() && this->getKeytime()) {

		this->backFromGame = true;
		this->states->push(new GameState(this->stateData, this->playerData, "mapEditor.txt"));
	}
}

void GameMenu::updateGui(const float& dt) {

	this->playerAvAnimComp->play("AV_IDLE", dt);
}

void GameMenu::updateInfoBox(const float& dt) {
}

void GameMenu::updateGold(const float& dt) {
}

void GameMenu::update(const float& dt) {

	if (this->backFromGame) {
		this->backFromGame = false;
		this->playerData->loadFromFile("playerData.txt");
		this->resetGUI();
	}

	this->updateKeytime(dt);
	this->updateMousePos();
	this->updateInput(dt);
	this->updateButtons();
	this->updateGui(dt);
	this->updateInfoBox(dt);
	this->updateGold(dt);
}

void GameMenu::renderButtons(sf::RenderTarget& target) {

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void GameMenu::renderGui(sf::RenderTarget& target) {

	target.draw(this->playerAv);
	target.draw(this->hpTxt);
	target.draw(this->dmgTxt);
}

void GameMenu::renderInfoBox(sf::RenderTarget& target) {

	target.draw(this->infoBox);
	target.draw(this->headerTxt);
	target.draw(this->infoTxt);
	target.draw(this->goldShapeBox);
	target.draw(this->costTxt);
}

void GameMenu::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	target->draw(this->bg);
	target->draw(this->goldTxt);
	target->draw(this->goldShapeTop);

	this->renderGui(*target);
	this->renderInfoBox(*target);
	this->renderButtons(*target);

}

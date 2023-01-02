#include "stdafx.h"
#include "GameState.h"

void GameState::initDefferedRender() {

	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0, 0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));

}

void GameState::initView() {

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
	));

	this->view.setCenter(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	));
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN MENU STATE");
	}
}

void GameState::initKeyBinds() {

	std::ifstream ifs("Config/gameStateKeyBinds.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}


void GameState::initTextures() {

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/playerSheet.png")) {
		throw "PLAYER TEXTURE ERROR";
	}

	if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Images/Sprites/enemySheet.png")) {
		throw "ENEMY TEXTURE ERROR";
	}

	if (!this->textures["WEAPON_SHEET"].loadFromFile("Resources/Images/Sprites/weapon.png")) {
		throw "WEAPON TEXTURE ERROR";
	}

	if (!this->textures["PICKABLE_SHEET"].loadFromFile("Resources/Images/Sprites/pickableSheet.png")) {
		throw "PICKABLE TEXTURE ERROR";
	}

}

void GameState::initPauseMenu() {
	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	
	this->pMenu = new PauseMenu(vm, this->font);

	this->pMenu->addButton(
		"QUIT", 
		gui::p2pY(13.8f, vm),
		gui::p2pX(18.75f, vm), 
		gui::p2pY(8.33f, vm), 
		gui::calcCharSize(vm),
		"QUIT"
	);
}

void GameState::initGameOverScreen() {

	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->gameOvecScr = new GameOver(vm, this->font, this->states);
}

void GameState::initShaders() {

	if(!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")){
		
		std::cout << "ERROR WITH SHADERS" << "\n";
	}
}

void GameState::initKeyTime() {

	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void GameState::initPlayer() {
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"], this->playerData);
}

void GameState::initPlayerGUI() {

	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem() {

	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::initTileMap() {

	this->tileMap = new TileMap("text.slmp");
}

void GameState::initSystems() {

	this->tts = new TextTagSystem("Fonts/trebuc.ttf");
}

GameState::GameState(StateData* stateData, PlayerData* playerData)
	: State(stateData) {

	this->playerData = playerData;
	this->gameOver = false;

	this->initDefferedRender();
	this->initView();
	this->initFonts();
	this->initKeyBinds();
	this->initTextures();
	this->initPauseMenu();
	this->initGameOverScreen();
	this->initShaders();
	this->initKeyTime();
	this->initPlayer();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();
	this->initSystems();
}

GameState::~GameState() {
	delete this->pMenu;
	delete this->gameOvecScr;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
	delete this->enemySystem;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++) {

		delete this->activeEnemies[i];
	}

	for (size_t i = 0; i < this->items.size(); i++) {

		delete this->items[i];
	}

	for (size_t i = 0; i < this->pickables.size(); i++) {

		delete this->pickables[i];
	}
}

const bool GameState::getKeyTime() {

	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax) {
		this->keyTimer.restart();
		return true;
	}

	return false;
}

void GameState::endState() {

	this->playerData->gainGold(this->goldCount);
	this->playerData->saveToFile("playerData.txt");
	this->states->pop();
}

void GameState::updateView(const float& dt) {

	this->view.setCenter(
		std::floor((this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 5.f) * 100.f) / 100.f,
		std::floor((this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 5.f) * 100.f) / 100.f
	);

	if (this->view.getSize().x <= this->tileMap->getMaxSizeF().x) {

		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {

			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);

		} else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x) {

			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}


	if (this->view.getSize().y <= this->tileMap->getMaxSizeF().y) {
	
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f) {

			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);

		} else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y) {

			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPos.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPos.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime()) {

		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player->move(0.f, 1.f, dt);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (this->player->getAttackTimer()) {

			//this->tts->addTextTag(DEFAULT_TAG, this->player->getCenter().x, this->player->getCenter().y, "test");
			this->items.push_back(new Kunai(true, 
				this->player->getCenter().x, this->player->getCenter().y, 
				this->player->getAttributeComponent()->dmg,
				this->textures["WEAPON_SHEET"], this->mousePosView));
		}
	}
}

void GameState::updatePlayerGUI(const float& dt) {

	this->playerGUI->update(dt, goldCount, killCount);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && this->getKeyTime()) {

		this->playerGUI->toggleCharacterTab();
	}*/

}

void GameState::updatePauseMenuButtons() {
	if (this->pMenu->isButtonPressed("QUIT") && this->getKeytime()) {
		this->endState();
	}
}

void GameState::updateTileMap(const float& dt) {

	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);

	//this->tileMap->update(this->player, dt);
}

void GameState::updatePlayer(const float& dt) {

	this->player->update(dt, this->mousePosView);

	if (this->player->getAttributeComponent()->isDead()) {
		this->gameOver = true;
	}

}

void GameState::updateEnemies(const float& dt) {

	unsigned index = 0;
	for (auto* enemy : this->activeEnemies) {

		enemy->update(dt, this->mousePosView);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);

		this->updateCombat(enemy, index, dt);

		if (enemy->isDead()) {

			this->enemySystem->removeEnemy(index, &this->pickables);
			++this->killCount;
			--index;
		}

		++index;
	}

}

void GameState::updateItems(const float& dt) {

	unsigned index = 0;
	for (auto* item : this->items) {

		item->update(dt);

		if (item->isWeapon() && !item->isToDestroy()) {

			Kunai* weapon = dynamic_cast<Kunai*>(item);
			weapon->setToDestroy(this->tileMap->checkCollide(weapon->getCenter(), dt));
		}

		if (item->isToDestroy()) {

			delete this->items[index];
			this->items.erase(this->items.begin() + index);
			--index;

		}

		++index;
	}
}

void GameState::updatePickables(const float& dt) {

	unsigned index = 0;
	for (auto* pickable : this->pickables) {

		pickable->update(dt);

		if (pickable->canPick(*this->player)) {
			pickable->onPick(*this->player, this->goldCount);
		}

		if (pickable->isPicked()) {

			delete this->pickables[index];
			this->pickables.erase(this->pickables.begin() + index);
			--index;
		}

		++index;
	}
}


void GameState::updateCombat(Enemy* enemy, const int index, const float& dt) {

	for (auto* item : this->items) {

		if (item->isWeapon() && !item->isToDestroy() && enemy->getGlobalBounds().intersects(item->getGlobalBounds())) {
			Kunai* weapon = dynamic_cast<Kunai*>(item);

			int dmg = static_cast<int>(weapon->getDamage());

			enemy->takeDamage(dmg);
			enemy->resetDamageTimer();
			this->tts->addTextTag(TAGTYPES::DEFAULT_TAG, enemy->getCenter().x - 50.f, enemy->getCenter().y - 10.f, dmg, "", "DMG");
			weapon->setToDestroy(true);
		}

	}

	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer()) {
		int dmg = enemy->getAttributeComp()->dmg;
		this->player->loseHP(dmg);
		this->tts->addTextTag(TAGTYPES::DAMAGE_TAG, player->getPosition().x - 20.f, player->getPosition().y, dmg, "-", "HP");
	}
}

void GameState::update(const float& dt) {

	this->updateMousePos(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused && !this->gameOver) {

		this->updateView(dt);
		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->updatePlayer(dt);

		this->updatePlayerGUI(dt);

		this->updateEnemies(dt);
		this->updateItems(dt);
		this->updatePickables(dt);

		this->tts->update(dt);

	} else if(this->paused && !this->gameOver) {

		this->pMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	} else {

		this->gameOvecScr->update(this->mousePosWindow);
	}

}

void GameState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(this->renderTexture, 
		this->viewGridPos, 
		&this->coreShader, 
		this->player->getCenter(),
		true
	);

	for (auto* pickable : this->pickables) {

		pickable->render(this->renderTexture, &this->coreShader, this->player->getCenter());
	}

	for (auto* enemy : this->activeEnemies) {

		enemy->render(this->renderTexture, &this->coreShader, this->player->getCenter(), true);
	}

	for (auto* item : this->items) {

		item->render(this->renderTexture, &this->coreShader, this->player->getCenter());
	}

	this->player->render(this->renderTexture, &this->coreShader, this->player->getCenter(), true);

	this->tileMap->renderDeferred(
		this->renderTexture, 
		&this->coreShader,
		this->player->getCenter()
	);

	this->tts->render(this->renderTexture);

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused && !this->gameOver) {
		
		this->pMenu->render(this->renderTexture);
	} else if (this->gameOver) {

		this->gameOvecScr->render(this->renderTexture);
	}

	//FINAL 

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
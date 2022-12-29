#include "stdafx.h"
#include "EnemyEditorMode.h"

void EnemyEditorMode::initVariables() {

	this->type = 0;
	this->amount = 1;
	this->timeToSpawn = 60;
	this->maxDist = 1000.f;

}

void EnemyEditorMode::initGui() {

	this->cursorTxt.setFont(*this->editorStateData->font);
	this->cursorTxt.setCharacterSize(12);
	this->cursorTxt.setFillColor(sf::Color::White);

	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineThickness(1.f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

}

EnemyEditorMode::EnemyEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	: EditorMode(stateData, tileMap, editorStateData) {

	this->initVariables();
	this->initGui();
}

EnemyEditorMode::~EnemyEditorMode() {
}

void EnemyEditorMode::updateInput(const float& dt) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
				this->type, this->amount, this->timeToSpawn, this->maxDist);

		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TYPE_UP"))) && this->getKeytime()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

			if (this->type > 0)
				this->type--;
		} else if (this->type < 100)
			this->type++;
		else
			this->type = 0;

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("AMOUNT_UP"))) && this->getKeytime()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

			if (this->amount > 0)
				this->amount--;
		} else if (this->amount < 100)
			this->amount++;
		else
			this->amount = 0;

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TTS_UP"))) && this->getKeytime()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

			if (this->timeToSpawn > 0)
				this->timeToSpawn--;
		} else if (this->timeToSpawn < 1000)
			this->timeToSpawn++;
		else
			this->timeToSpawn = 0;

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("MD_UP"))) && this->getKeytime()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

			if (this->maxDist > 0)
				this->maxDist--;
		} else if (this->maxDist < 10-0)
			this->maxDist++;
		else
			this->maxDist = 0;

	}

}

void EnemyEditorMode::updateGui(const float& dt) {

	this->selectorRect.setPosition(
		this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
		this->editorStateData->mousePosGrid->y * this->stateData->gridSize
	);

	this->cursorTxt.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss <<
		"\n" << "Enemy type: " << this->type <<
		"\n" << "Enemy amount: " << this->amount <<
		"\n" << "Time to spawn: " << this->timeToSpawn <<
		"\n" << "Max distance: " << this->maxDist;

	this->cursorTxt.setString(ss.str());

}

void EnemyEditorMode::update(const float& dt) {

	this->updateInput(dt);
	this->updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target) {

	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorTxt);

	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget& target) {

	this->renderGui(target);
}

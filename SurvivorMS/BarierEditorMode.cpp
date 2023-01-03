#include "stdafx.h"
#include "BarierEditorMode.h"

void BarierEditorMode::initVariables() {

	this->lvl = 10;
}

void BarierEditorMode::initGui() {

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

BarierEditorMode::BarierEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData) 
	: EditorMode(stateData, tileMap, editorStateData) {

	this->initVariables();
	this->initGui();
}

BarierEditorMode::~BarierEditorMode() {
}

void BarierEditorMode::updateInput(const float& dt) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->lvl);

		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::BLOCKADE);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TYPE_INC"))) && this->getKeytime()) {

		++this->lvl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TYPE_DEC"))) && this->getKeytime()) {

		--this->lvl;
	}
}

void BarierEditorMode::updateGui(const float& dt) {

	this->selectorRect.setPosition(
		this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
		this->editorStateData->mousePosGrid->y * this->stateData->gridSize
	);

	this->cursorTxt.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss <<
		"\n" << "Blockade lvl: " << this->lvl;

	this->cursorTxt.setString(ss.str());
}

void BarierEditorMode::update(const float& dt) {

	this->updateInput(dt);
	this->updateGui(dt);
}

void BarierEditorMode::renderGui(sf::RenderTarget& target) {

	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorTxt);

	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void BarierEditorMode::render(sf::RenderTarget& target) {

	this->renderGui(target);
}

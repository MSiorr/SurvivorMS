#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables() {

	this->textureRect = sf::IntRect(
		0, 0,
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);

	this->collision = false;
	this->type = TileTypes::DEFAULT;

	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui() {

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

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 6 * 64.f, 8 * 64.f,
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		*this->editorStateData->font, "TS");

}

DefaultEditorMode::DefaultEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	: EditorMode(stateData, tileMap, editorStateData) {

	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode() {

	delete this->textureSelector;
}

void DefaultEditorMode::updateInput(const float& dt) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			if (!this->textureSelector->getActive()) {

				if (this->tileAddLock) {

					if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
						this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);

				} else
					this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);

			} else {

				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {

			if (!this->textureSelector->getActive()) {

				this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
			} else {

			}
		}


	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TOGGLE_COLLISION"))) && this->getKeytime()) {

		this->collision = !this->collision;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TYPE_INC"))) && this->getKeytime()) {

		++this->type;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TYPE_DEC"))) && this->getKeytime()) {

		this->type = std::max(0, this->type - 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keyBinds->at("TOGGLE_TILE_LOCK"))) && this->getKeytime()) {

		this->tileAddLock = !this->tileAddLock;
	}

}

void DefaultEditorMode::updateGui(const float& dt) {

	this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);

	if (!this->textureSelector->getActive()) {

		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(
			this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
			this->editorStateData->mousePosGrid->y * this->stateData->gridSize
		);
	}


	this->cursorTxt.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss << this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y <<
		"\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\n" << "Collision: " << this->collision <<
		"\n" << "Type: " << this->type <<
		"\n" << "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) <<
		"\n" << "Tile lock: " << this->tileAddLock;

	this->cursorTxt.setString(ss.str());

}

void DefaultEditorMode::update(const float& dt) {

	this->updateInput(dt);
	this->updateGui(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget& target) {

	if (!this->textureSelector->getActive()) {

		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(*this->editorStateData->view);
	target.draw(this->cursorTxt);

}

void DefaultEditorMode::render(sf::RenderTarget& target) {

	this->renderGui(target);
}

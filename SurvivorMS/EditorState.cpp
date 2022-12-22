#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables() {

}

void EditorState::initBackground() {

}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("Fonts/trebuc.ttf")) {
		throw("ERROR::LOAD FONT IN EDITOR STATE");
	}
}

void EditorState::initKeyBinds() {

	std::ifstream ifs("Config/editorStateKeyBinds.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void EditorState::initButtons() {


}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys, std::stack<State*>* states)
	: State(window, suppKeys, states) {

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeyBinds();
	this->initButtons();

	//this->bg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->bg.setFillColor(sf::Color::Blue);
}

EditorState::~EditorState() {

	for (auto& it : this->buttons) {
		delete it.second;
	}

}

void EditorState::updateInput(const float& dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
		this->endState();
	}

}

void EditorState::updateButtons() {

	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}
}

void EditorState::update(const float& dt) {

	this->updateMousePos();

	this->updateInput(dt);

	this->updateButtons();

}

void EditorState::renderButtons(sf::RenderTarget& target) {
	//this->testBtn->render(target);

	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target) {

	if (!target)
		target = this->window;

	this->renderButtons(*target);
}

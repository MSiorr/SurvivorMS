#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id ) {

	this->btnState = BUTTONSTATES::BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 1.2f
	);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;
}

gui::Button::~Button() {
}

const bool gui::Button::isPressed() const {

	if (this->btnState == BUTTONSTATES::BTN_ACTIVE) {
		return true;
	}

	return false;
}

const std::string gui::Button::getText() const {
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const {
	return this->id;
}

void gui::Button::setText(const std::string text) {
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id) {
	this->id = id;
}

void gui::Button::update(const sf::Vector2f& mousePos) {

	this->btnState = BUTTONSTATES::BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->btnState = BUTTONSTATES::BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->btnState = BUTTONSTATES::BTN_ACTIVE;
		}
	}

	switch (this->btnState) {
	case BUTTONSTATES::BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->text.setOutlineColor(this->outlineIdleColor);
		break;
	case BUTTONSTATES::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->text.setOutlineColor(this->outlineHoverColor);
		break;
	case BUTTONSTATES::BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->text.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->text.setOutlineColor(sf::Color::Green);
		break;
	}


}

void gui::Button::render(sf::RenderTarget& target) {

	target.draw(this->shape);
	target.draw(this->text);

}


// =============================================================


gui::DropDownList::DropDownList(
	float x, float y, float width, float height,
	sf::Font& font, std::string list[], 
	unsigned elementsCount, unsigned defaultIndex
) :
	font(font), showList(false), keytimeMax(1.f), keytime(0.f) {

	this->activeElement = new gui::Button(
		x, y,
		width, height,
		&this->font, list[defaultIndex], 12,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(0, 0, 0, 200), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < elementsCount; i++) {
		this->list.push_back(
			new gui::Button(
				x, y + ((i+1) * height),
				width, height,
				&this->font, list[i], 12,
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(0, 0, 0, 200), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0), i)
		);
	}

}

gui::DropDownList::~DropDownList() {
	delete this->activeElement;
	
	for (size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}

const bool gui::DropDownList::getKeytime() {
	
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	
	return false;
}

const unsigned short& gui::DropDownList::getActiveElementID() const {
	return this->activeElement->getId();
}

void gui::DropDownList::updateKeytime(const float& dt) {
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt) {

	this->updateKeytime(dt);
	this->activeElement->update(mousePos);

	if (this->activeElement->isPressed() && this->getKeytime()) {
		this->showList = !this->showList;
	}

	if (this->showList) {
		for (auto& it : this->list) {
			it->update(mousePos);

			if (it->isPressed() && this->getKeytime()) {
				this->showList = false;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	}

}

void gui::DropDownList::render(sf::RenderTarget& target) {
	this->activeElement->render(target);

	if (this->showList) {
		for (auto& it : this->list)
			it->render(target);
	}
}

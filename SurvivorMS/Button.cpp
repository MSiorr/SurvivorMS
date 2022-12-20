#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {

	this->btnState = BUTTONSTATES::BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button() {
}

const bool Button::isPressed() const {

	if (this->btnState == BUTTONSTATES::BTN_ACTIVE) {
		return true;
	}

	return false;
}

void Button::update(const sf::Vector2f mousePos) {

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
		break;
	case BUTTONSTATES::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BUTTONSTATES::BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		break;
	}


}

void Button::render(sf::RenderTarget* target) {

	target->draw(this->shape);
	target->draw(this->text);

}

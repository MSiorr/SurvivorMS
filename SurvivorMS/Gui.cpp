#include "stdafx.h"
#include "Gui.h"


const float gui::p2pX(const float perc, const sf::VideoMode& vm) {

	//convert % value to pixel value relative to reoslution in the X-axis

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm) {

	//convert % value to pixel value relative to reoslution in the Y-axis

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm) {

	//calculate character size for curr resolution

	return static_cast<unsigned>((vm.width + vm.height) / 66);
}

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
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 1.9f,
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

void gui::Button::update(const sf::Vector2i& mousePos) {

	this->btnState = BUTTONSTATES::BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
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
	float fontSize, sf::Font& font, std::string list[], 
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

	for (unsigned i = 0; i < elementsCount; i++) {
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

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt) {

	this->updateKeytime(dt);
	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytime()) {
		this->showList = !this->showList;
	}

	if (this->showList) {
		for (auto& it : this->list) {
			it->update(mousePosWindow);

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


// ========================================================================


gui::TextureSelector::TextureSelector(float x, float y, float width, float height, 
	float gridSize, const sf::Texture* textureSheet, 
	sf::Font& font, std::string text) : keytimeMax(1.f), keytime(0.f) {

	this->gridSize = gridSize;
	this->active = false;

	float offset = gridSize;

	this->hidden = false;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*textureSheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width) {

		this->sheet.setTextureRect(sf::IntRect(
			0, 0, 
			static_cast<int>(this->bounds.getGlobalBounds().width), 
			static_cast<int>(this->bounds.getGlobalBounds().height)
		));
	}
	
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
		
		this->sheet.setTextureRect(sf::IntRect(
			0, 0, 
			static_cast<int>(this->bounds.getGlobalBounds().height),
				static_cast<int>(this->bounds.getGlobalBounds().width)
		));

	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Blue);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hideBtn = new gui::Button(
		x, y,
		40.f, 40.f,
		&font, text, 16,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(140, 140, 140, 200), sf::Color(140, 140, 140, 140), sf::Color(140, 140, 140, 50));;

}

gui::TextureSelector::~TextureSelector() {
	delete this->hideBtn;
}

const bool& gui::TextureSelector::getActive() const {
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const {
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytime() {

	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void gui::TextureSelector::updateKeytime(const float& dt) {
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt) {

	this->updateKeytime(dt);

	this->hideBtn->update(mousePosWindow);

	if (this->hideBtn->isPressed() && this->getKeytime()) {
		
		this->hidden = !this->hidden;
	}
	
	if (!this->hidden) {

		this->active = false;

		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {

			this->active = true;
 
			if (this->active) {

				this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
				this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
		
				this->selector.setPosition(
					this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
					this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
				);

				this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
				this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
			}
		}
	}

}

void gui::TextureSelector::render(sf::RenderTarget& target) {

	if (!this->hidden) {
		target.draw(this->bounds);
		target.draw(this->sheet);

		if(this->active)
			target.draw(this->selector);
	}

	this->hideBtn->render(target);
}


// ==============================================


gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height, float charSizeMultip, int maxValue, sf::Color innerColor, sf::VideoMode& vm, sf::Font* font) {
	
	float width = gui::p2pX(_width, vm);
	float height = gui::p2pY(_height, vm);
	float x = gui::p2pX(_x, vm);
	float y = gui::p2pY(_y, vm);

	this->maxWidth = width;
	this->maxValue = maxValue;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition(x, y);

	this->inner.setSize(sf::Vector2f(width, height));
	this->inner.setFillColor(innerColor);
	this->inner.setPosition(this->back.getPosition());

	if (font) {
		this->text.setFont(*font);
		this->text.setCharacterSize(static_cast<unsigned>(gui::calcCharSize(vm) * charSizeMultip));
		this->text.setPosition(
			this->inner.getPosition().x + gui::p2pX(0.53f, vm),
			this->inner.getPosition().y + gui::p2pY(0.5f, vm)
		);
	}
}

gui::ProgressBar::~ProgressBar() {

}

void gui::ProgressBar::updateMaxVal(const float val) {

	this->maxValue = val;
}

void gui::ProgressBar::update(const int currVal) {

	float percent = static_cast<float>(currVal) / static_cast<float>(this->maxValue);

	this->inner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->maxWidth * percent)),
			this->inner.getSize().y
		)
	);

	this->barString = std::to_string(currVal) + " / " + std::to_string(maxValue);
	this->text.setString(this->barString);
}

void gui::ProgressBar::render(sf::RenderTarget& target) {

	target.draw(this->back);
	target.draw(this->inner);
	target.draw(this->text);
}
#ifndef BUTTON_H
#define BUTTON_H

enum BUTTONSTATES {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
	short unsigned btnState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned characterSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	const bool isPressed() const;

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* taget);
};

#endif 
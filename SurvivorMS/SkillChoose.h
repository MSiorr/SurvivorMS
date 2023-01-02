#ifndef SKILLCHOOSE_H
#define SKILLCHOOSE_H

#include "Gui.h"

class SkillChoose {
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape bg;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	SkillChoose(sf::VideoMode& vm, sf::Font& font);
	virtual ~SkillChoose();

	std::map<std::string, gui::Button*>& getButtons();

	const bool isButtonPressed(const std::string key);

	void addButton(const std::string key, float y, const float width, const float height, const unsigned charSize, const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif // !SKILLCHOOSE_H
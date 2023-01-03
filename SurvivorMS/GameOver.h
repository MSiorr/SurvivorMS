#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Gui.h"
#include "State.h"

class GameOver {
private:
	sf::VideoMode& vm;
	sf::Font& font;
	sf::Text gameOverTxt;

	sf::Text infoTxt;

	sf::RectangleShape bg;

	std::stack<State*>* states;

public:
	GameOver(sf::VideoMode& vm, sf::Font& font, std::stack<State*>* states);
	virtual ~GameOver();

	void setMainString(std::string str);

	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

#endif 

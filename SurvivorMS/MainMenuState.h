#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State {

private:
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initFonts();
	void initKeyBinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys);
	virtual ~MainMenuState();

	//Fun

	void endState();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#endif
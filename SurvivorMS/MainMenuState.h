#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
class MainMenuState :
    public State {

private:
	sf::RectangleShape bg;

	void initKeyBinds();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys);
	virtual ~MainMenuState();

	//Fun

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
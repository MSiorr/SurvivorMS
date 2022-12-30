#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "GameMenu.h"
#include "EditorState.h"
#include "SettingsState.h"

class GameState;
class EditorState;
class SettingsState;

class MainMenuState :
    public State {

private:

	sf::Texture bgTexture;
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	void initVariables();
	void initFonts();
	void initKeyBinds();
	void initGui();
	void resetGui();

public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	//Fun

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif
#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"

class State;

class SettingsState : public State {
private:

	sf::Texture bgTexture;
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	void initVariables();
	void initFonts();
	void initKeyBinds();
	void initGui();
	void resetGui();

public:
	SettingsState(StateData* stateData);
	virtual ~SettingsState();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif 
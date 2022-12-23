#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State {
private:
	PauseMenu* pMenu;

	sf::Texture bgTexture;
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeyBinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Fun

	void updateInput(const float& dt);
	void updateButtons();
	void updateGui();
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif

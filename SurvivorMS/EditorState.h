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
	sf::View view;

	PauseMenu* pMenu;

	sf::Text cursorTxt;

	sf::Texture bgTexture;
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	float cameraSpeed;
	bool collision;
	short type;

	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeyBinds();
	void initPauseMenu();
	void initButtons();
	void initTileMap();
	void initGui();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Fun

	void updateInput(const float& dt);
	void updateEditorCameraInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif

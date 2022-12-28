#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"
#include "DefaultEditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class EditorStateData;
class DefaultEditorMode;

enum EditorModes {DEFAULT_MODE = 0, ENEMY_MODE};


class EditorState :
    public State {
private:

	EditorStateData editorStateData;

	sf::View view;
	float cameraSpeed;

	PauseMenu* pMenu;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	std::vector<EditorMode*> modes;

	void initVariables();
	void initEditorStateData();
	void initView();
	void initFonts();
	void initKeyBinds();
	void initPauseMenu();
	void initButtons();
	void initTileMap();
	void initGui();

	void initModes();

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

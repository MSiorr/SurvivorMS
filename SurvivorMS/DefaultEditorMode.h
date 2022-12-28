#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;

class DefaultEditorMode :
	public EditorMode {
private:

	sf::Text cursorTxt;
	sf::RectangleShape sidebar;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;

	bool collision;
	short type;
	int layer;
	bool tileAddLock;

	void initVariables();
	void initGui();

protected:


public:
	DefaultEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~DefaultEditorMode();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif 
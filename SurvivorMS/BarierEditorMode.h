#ifndef BARIEREDITORMODE_H
#define BARIEREDITORMODE_H

#include "EditorMode.h"
class BarierEditorMode :
    public EditorMode {
private:

	sf::Text cursorTxt;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	int lvl;

	void initVariables();
	void initGui();

public:
	BarierEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~BarierEditorMode();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif
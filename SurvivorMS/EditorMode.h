#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class Tile;
class TileMap;


class EditorStateData {
public:
	EditorStateData() {};

	sf::View* view;
	sf::Font* font;

	float* keytime;
	float* keytimeMax;

	std::map<std::string, int>* keyBinds;

	sf::Vector2i* mousePosScreen;
	sf::Vector2i* mousePosWindow;
	sf::Vector2f* mousePosView;
	sf::Vector2i* mousePosGrid;
};


class EditorMode {
private:

protected:

	EditorStateData* editorStateData;
	StateData* stateData;

	TileMap* tileMap;

public:
	EditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~EditorMode();

	const bool getKeytime();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif 
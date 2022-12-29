#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;
class EnemySpawnerTile;


class EnemyEditorMode :
    public EditorMode {
private:

	sf::Text cursorTxt;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;

	sf::IntRect textureRect;

	int type;
	int amount;
	int timeToSpawn;
	float maxDist;

	void initVariables();
	void initGui();

public:
	EnemyEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~EnemyEditorMode();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif 

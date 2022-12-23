#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState : public State {
private:
	sf::Font font;
	PauseMenu* pMenu;

	Player* player;

	TileMap* tileMap;

	void initFonts();
	void initKeyBinds();
	void initTextures();
	void initPauseMenu();
	void initPlayer();
	void initTileMap();

public:
	GameState(StateData* stateData);
	virtual ~GameState();

	//Fun

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
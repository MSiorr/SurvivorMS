#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class PauseMenu;
class TileMap;
class State;
class Player;
class PlayerGUI;

class GameState : public State {
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pMenu;

	Player* player;
	PlayerGUI* playerGUI;

	TileMap* tileMap;
	void initDefferedRender();
	void initView();
	void initFonts();
	void initKeyBinds();
	void initTextures();
	void initPauseMenu();
	void initPlayer();
	void initPlayerGUI();
	void initTileMap();

public:
	GameState(StateData* stateData);
	virtual ~GameState();

	//Fun
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
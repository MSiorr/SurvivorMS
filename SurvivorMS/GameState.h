#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Kunai.h"
#include "Enemy.h"

class PauseMenu;
class TileMap;
class State;
class Player;
class PlayerGUI;
class Kunai;
class Enemy;

class GameState : public State {
private:
	sf::View view;
	sf::Vector2i viewGridPos;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pMenu;

	sf::Shader coreShader;

	Player* player;
	PlayerGUI* playerGUI;

	TileMap* tileMap;

	std::vector<Enemy*> activeEnemies;

	void initDefferedRender();
	void initView();
	void initFonts();
	void initKeyBinds();
	void initTextures();
	void initPauseMenu();
	void initShaders();
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
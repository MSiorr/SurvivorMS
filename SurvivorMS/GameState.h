#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Kunai.h"
#include "TextTagSystem.h"
#include "PlayerData.h"
#include "GameOver.h"
#include "Pickable.h"

class GameState : public State {
private:
	sf::View view;
	sf::Vector2i viewGridPos;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pMenu;
	GameOver* gameOvecScr;

	sf::Shader coreShader;

	Player* player;
	PlayerGUI* playerGUI;

	TileMap* tileMap;

	std::vector<Enemy*> activeEnemies;
	EnemySystem* enemySystem;

	std::vector<Item*> items;
	std::vector<Pickable*> pickables;

	TextTagSystem* tts;

	sf::Clock keyTimer;
	float keyTimeMax;

	PlayerData* playerData;
	bool gameOver;

	int goldCount;
	int killCount;

	void initDefferedRender();
	void initView();
	void initFonts();
	void initKeyBinds();
	void initTextures();
	void initPauseMenu();
	void initGameOverScreen();
	void initShaders();
	void initKeyTime();
	void initPlayer();
	void initPlayerGUI();
	void initEnemySystem();
	void initTileMap();
	void initSystems();

public:
	GameState(StateData* stateData, PlayerData* playerData);
	virtual ~GameState();

	const bool getKeyTime();

	void endState();

	//Fun
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void updatePlayer(const float& dt);
	void updateEnemies(const float& dt);
	void updateItems(const float& dt);
	void updatePickables(const float& dt);
	void updateCombat(Enemy* enemy, const int index, const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget* target = NULL);
};

#endif
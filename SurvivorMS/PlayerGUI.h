#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "PlayerGUITabs.h"

class Player;

class PlayerGUI {
private:
	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	// Level Bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	// EXP Bar
	gui::ProgressBar* expBar;

	// HP Bar
	gui::ProgressBar* hpBar;

	PlayerGUITabs* playerTabs;


	void initFont();
	void initHPBar();
	void initExpBar();
	void initLevelBar();

	void initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player);

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	const bool getTabsOpen() const;
	void toggleCharacterTab();

	void updateHPBar();
	void updateExpBar();
	void updateLevelBar();
	void updatePlayerTabs();

	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

#endif 
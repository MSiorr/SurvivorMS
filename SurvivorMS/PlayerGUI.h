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

	sf::RectangleShape goldIcon;
	sf::RectangleShape skullIcon;

	sf::Texture goldTexture;
	sf::Texture skullTexture;

	sf::Text goldTxt;
	sf::Text killCountTxt;

	PlayerGUITabs* playerTabs;


	void initFont();
	void initExpBar();
	void initLevelBar();
	void initGold();
	void initKillCounter();
	void initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player);

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	const bool getTabsOpen() const;
	void toggleCharacterTab();

	void updateExpBar();
	void updateLevelBar();
	void updatePlayerTabs();
	void updateGold(const float& gold);
	void updateKillCounter(const float& kills);

	void update(const float& dt, const float& gold, const float& kills);

	void renderExpBar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);
	void renderGold(sf::RenderTarget& target);
	void renderKillCounter(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

#endif 
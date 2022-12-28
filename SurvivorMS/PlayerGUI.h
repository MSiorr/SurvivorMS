#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "Gui.h"

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


	void initFont();
	void initHPBar();
	void initExpBar();
	void initLevelBar();

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	void updateHPBar();
	void updateExpBar();
	void updateLevelBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void renderLevelBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif 
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
private:
	Player* player;

	void initKeyBinds();
	void initTextures();
	void initPlayer();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Fun

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Entity.h"

class GameState : public State {
private:
	Entity player;

	void initKeyBinds();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys);
	virtual ~GameState();

	//Fun

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
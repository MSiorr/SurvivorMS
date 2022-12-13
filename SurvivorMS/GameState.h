#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
private:


public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	//Fun
	void endState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif
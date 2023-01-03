#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "Gui.h"
#include "GraphicsSettings.h"

class State;

class StateData {
public:
	StateData() {
		this->window = nullptr;
		this->suppKeys = nullptr;
		this->states = nullptr;
		this->gfxSettings = nullptr;
		this->gridSize = 0.f;
	};

	sf::RenderWindow* window;
	float gridSize;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* suppKeys;
	std::stack<State*>* states;
};

class State {
private:

protected:
	StateData* stateData;

	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	bool quit;
	bool paused;

	float keytime;
	float keytimeMax;

	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	std::map<std::string, sf::Texture> textures;

	virtual void initKeyBinds() = 0;

public:
	State(StateData* stateData);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	void pauseState();
	void unpauseState();
	virtual void endState();

	virtual void updateMousePos(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif
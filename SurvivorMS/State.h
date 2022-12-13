#ifndef STATE_H
#define STATE_H

class State {
private:

protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	bool quit;

	std::vector<sf::Texture> textures;
	std::map<std::string, int> keyBinds;

	virtual void initKeyBinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* suppKeys);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkQuit();

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif
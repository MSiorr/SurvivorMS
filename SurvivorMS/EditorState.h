#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
class EditorState :
    public State {
private:
	sf::Texture bgTexture;
	sf::RectangleShape bg;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeyBinds();
	void initButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* suppKeys, std::stack<State*>* states);
	virtual ~EditorState();

	//Fun

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif

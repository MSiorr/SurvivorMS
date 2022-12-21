#include "MainMenuState.h"

#ifndef GAME_H
#define GAME_H


class Game {
private:

    // Var
    sf::RenderWindow* window;

    sf::Event ev;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;

    bool fullscreen;

    sf::Clock dtTime;
    float dt; // deltaTime

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;


    // Init
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();

public:
    Game();
    ~Game();

    // Fun
    void endApp();

    void updateDt();
    void pollEvents();
    void update();

    void render();

    void run();
};

#endif
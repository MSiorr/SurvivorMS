#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class MainMenuState;

class Game {
private:

    StateData stateData;
    GraphicsSettings gfxSettings;
    sf::RenderWindow* window;
    sf::Event ev;

    sf::Clock dtTime;
    float dt; // deltaTime

    float gridSize;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;


    // Init
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
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
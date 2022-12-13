#include "GameState.h"

#ifndef GAME_H
#define GAME_H


class Game {
private:

    // Var
    sf::RenderWindow* window;

    sf::Event ev;

    sf::Clock dtTime;
    float dt; // deltaTime

    std::stack<State*> states;


    // Init
    void initVariables();
    void initWindow();
    void initStates();

public:
    Game();
    ~Game();

    // Fun
    void updateDt();
    void pollEvents();
    void update();
    void render();
    void run();
};

#endif
#ifndef COIN_H
#define COIN_H

#include "Pickable.h"

class Coin :
    public Pickable {
private:

    int gold;

public:
    Coin(sf::Vector2f pos, sf::Texture& textureSheet);
    ~Coin();

    void onPick(Player& player, int& goldCount);

    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f());
};

#endif // !COIN_H
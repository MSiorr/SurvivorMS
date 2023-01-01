#ifndef EXPGEM_H
#define EXPGEM_H

#include "Pickable.h"

class ExpGem :
    public Pickable {
private:

    int exp;

public:
    ExpGem(sf::Vector2f pos, sf::Texture& textureSheet);
    ~ExpGem();

    void onPick(Player& player, int& goldCount);

    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f());
};

#endif // !COIN_H
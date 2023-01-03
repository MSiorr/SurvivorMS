#pragma once
#include "Pickable.h"
class Meat :
    public Pickable {
private:

    float hpMultipHeal;

public:
    Meat(sf::Vector2f pos, sf::Texture& textureSheet);
    ~Meat();

    void onPick(Player& player, int& goldCount);

    void update(const float& dt);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos);
};


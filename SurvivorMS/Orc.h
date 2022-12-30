#ifndef ORC_H
#define ORC_H

#include "Enemy.h"
class Orc :
    public Enemy {
private:

	sf::RectangleShape hpBar;

	void initVariables();
	void initAnimations();
	void initGui();

public:
	Orc(float x, float y, sf::Texture& textureSheet, EnemySpawnerTile& enemySpawnerTile);
	virtual ~Orc();

	void takeDamage(const int damage);

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox);
};

#endif 
#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "AIFollow.h"

class Boss :
    public Enemy {
private:

	sf::RectangleShape hpBar;

	AIFollow* follow;

	void initVariables();
	void initAnimations();
	void initAI();
	void initGui();

public:
	Boss(float x, float y, sf::Texture& textureSheet, EnemySpawnerTile& enemySpawnerTile, Entity& player);
	virtual ~Boss();

	void takeDamage(const int damage);
	const bool getDmgTimer();

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox);
};

#endif // !BOSS_H
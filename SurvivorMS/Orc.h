#ifndef ORC_H
#define ORC_H

#include "Enemy.h"
#include "AIFollow.h"
class Orc :
    public Enemy {
private:

	sf::RectangleShape hpBar;

	AIFollow* follow;

	void initVariables();
	void initAnimations();
	void initAI();
	void initGui();

public:
	Orc(float x, float y, sf::Texture& textureSheet, EnemySpawnerTile& enemySpawnerTile, Entity& player);
	virtual ~Orc();

	void takeDamage(const int damage);

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox);
};

#endif 
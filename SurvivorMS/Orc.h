#ifndef ORC_H
#define ORC_H

#include "Enemy.h"
class Orc :
    public Enemy {
private:

	void initVariables();
	void initAnimations();

public:
	Orc(float x, float y, sf::Texture& textureSheet);
	virtual ~Orc();

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPos, const bool showHitbox);
};

#endif 
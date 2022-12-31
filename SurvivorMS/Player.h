#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Kunai.h"

class Entity;

class Player :
	public Entity {
private:

	bool attacking;

	Kunai* weapon;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

	void initVariables();
	void initComponents();
	void initAnimations();

public:
	Player(float x, float y, sf::Texture& textureSheet);
	virtual ~Player();

	AttributeComponent* getAttributeComponent();
	Kunai* getWeapon() const;
	const bool getDamageTimer();
	const bool getAttackTimer();

	const std::string toStringCharacterTab() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseExp(const int exp);
	void gainExp(const int exp);

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false);
};

#endif 
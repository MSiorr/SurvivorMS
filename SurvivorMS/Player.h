#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Kunai.h"
#include "PlayerData.h"

class Entity;

class Player :
	public Entity {
private:

	bool attacking;

	sf::RectangleShape hpBar;

	Kunai* weapon;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

	void initVariables();
	void initComponents();
	void initAnimations();
	void initGui();

public:
	Player(float x, float y, sf::Texture& textureSheet, PlayerData* playerData);
	virtual ~Player();

	AttributeComponent* getAttributeComponent();
	Kunai* getWeapon() const;
	const bool getDamageTimer();
	const bool getAttackTimer();

	const std::string toStringCharacterTab() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainExp(const int exp);

	void lvlUpSkill(const int key);

	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false);
};

#endif 
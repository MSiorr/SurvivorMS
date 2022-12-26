#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent {
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& spirte, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	void setPosition(const sf::Vector2f& pos);
	void setPosition(const float x, const float y);

	bool intersect(const sf::FloatRect& frect);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 
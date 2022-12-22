#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum MOVEMENTSTATE { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT };

class MovementComponent {
private:
	sf::Sprite& sprite;

	float maxVelocity;

	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	const bool getState(const short unsigned state) const;

	void move(const float dirX, const float dirY, const float& dt);
	void update(const float& dt);
};

#endif
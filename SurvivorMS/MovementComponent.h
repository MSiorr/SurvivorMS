#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

class MovementComponent {
private:
	float maxVelocity;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

public:
	MovementComponent(float maxVelocity);
	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float dirX, const float dirY);
	void update(const float& dt);
};

#endif
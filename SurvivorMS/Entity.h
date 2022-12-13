#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:

protected:
	sf::RectangleShape shape;
	float moveSpeed;

public:
	Entity();
	virtual ~Entity();

	virtual void move(const float& dt, const float dirX, const float dirY);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};

#endif
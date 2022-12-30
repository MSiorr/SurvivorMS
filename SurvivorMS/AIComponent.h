#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Entity.h"
#include "Player.h"

class AIComponent {
private:

	Entity& entity;
	Entity& self;

public:
	AIComponent(Entity& self, Entity& entity);
	~AIComponent();

	void update(const float& dt);
};

#endif
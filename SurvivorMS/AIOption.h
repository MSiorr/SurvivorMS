#ifndef AIOPTION_H
#define AIOPTION_H

#include "Entity.h"

class AIOption {
private:

protected:
	Entity& self;
	Entity& entity;

public:
	AIOption(Entity& self, Entity& entity);
	~AIOption();

	virtual void update(const float& dt) = 0;
};

#endif // !AIOPTION_H
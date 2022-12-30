#ifndef AIOFOLLOW_H
#define AIOFOLLOW_H

#include "AIOption.h"

class AIFollow :
    public AIOption {

private:

public:
    AIFollow(Entity& self, Entity& entity);
    ~AIFollow();

    void update(const float& dt);
};

#endif
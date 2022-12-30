#include "stdafx.h"
#include "VectorMath.h"

const float vectorDistance(const float x1, const float y1, const float x2, const float y2) {
    
    const float dX = x2 - x1;
    const float dY = y2 - y1;

    return sqrt(pow(dX, 2) + pow(dY, 2));
}

const float vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2) {
    
    const sf::Vector2f dVec = vec2 - vec1;

    return sqrt(pow(dVec.x, 2) + pow(dVec.y, 2));
}

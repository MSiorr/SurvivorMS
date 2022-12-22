#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet) {
}

AnimationComponent::~AnimationComponent() {
	for (auto &it : this->animations) {
		delete it.second;
	}
}

void AnimationComponent::addAnim(
	const std::string key, float animSpeed,
	int startFrameX, int startFrameY,
	int framesX, int framesY,
	int width, int height
) {
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet, animSpeed,
		startFrameX, startFrameY, framesX, framesY, width, height
	);
}

void AnimationComponent::play(const std::string key, const float& dt) {
	this->animations[key]->play(dt);
}

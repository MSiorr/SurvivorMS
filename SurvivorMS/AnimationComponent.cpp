#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet), lastAnim(NULL) {
}

AnimationComponent::~AnimationComponent() {
	for (auto &it : this->animations) {
		delete it.second;
	}
}

const bool& AnimationComponent::isDone(const std::string key) {
	return this->animations[key]->isDone();
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

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority) {
	if (!this->priorityAnim || this->priorityAnim == this->animations[key]) {

		if (!this->priorityAnim && priority) { // SET PRIORITY
			this->priorityAnim = this->animations[key];
		}

		if (this->lastAnim != this->animations[key]) {

			if(this->lastAnim != NULL)
				this->lastAnim->reset();

			this->lastAnim = this->animations[key];
		}

		if (this->animations[key]->play(dt) && this->priorityAnim) {
			this->priorityAnim = NULL;
		}
	} 

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority) {

	if (!this->priorityAnim || this->priorityAnim == this->animations[key]) {

		if (!this->priorityAnim && priority) { // SET PRIORITY
			this->priorityAnim = this->animations[key];
		}

		if (this->lastAnim != this->animations[key]) {

			if (this->lastAnim != NULL)
				this->lastAnim->reset();

			this->lastAnim = this->animations[key];
		}

		if (this->animations[key]->play(dt, abs(modifier / modifierMax)) && this->priorityAnim) {
			this->priorityAnim = NULL;
		}
	}

	return this->animations[key]->isDone();

}



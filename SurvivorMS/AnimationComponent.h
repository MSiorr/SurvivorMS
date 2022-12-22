#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

class AnimationComponent {
private:

	class Animation {
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;

		float animSpeed;
		float timer;
		bool done;
		int width;
		int height;

		sf::IntRect startRect;
		sf::IntRect currRect;
		sf::IntRect endRect;

		Animation(
			sf::Sprite& sprite, sf::Texture& textureSheet,
			float animSpeed,
			int startFrameX, int startFrameY,
			int framesX, int framesY,
			int width, int height
		)
			: sprite(sprite), textureSheet(textureSheet), 
			animSpeed(animSpeed), timer(0.f), done(false), width(width), height(height) 
		{
			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currRect = this->startRect;
			this->endRect = sf::IntRect(framesX * width, framesY * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
			this->sprite.setScale(4, 4);
		}

		const bool& isDone() const {
			return this->done;
		}

		const bool& play(const float& dt) {

			this->done = false;

			this->timer += 100.f * dt;

			if (this->timer >= this->animSpeed) {
				this->timer = 0.f;

				if (this->currRect != this->endRect) { // NEXT FRAME
					this->currRect.left += this->width;
				} else { // RESET
					this->currRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currRect);
			}

			return this->done;
		}

		const bool& play(const float& dt, float modPercent) {

			if (modPercent < 0.5f)
				modPercent = 0.5f;

			this->done = false;

			this->timer += modPercent * 100.f * dt;

			if (this->timer >= this->animSpeed) {
				this->timer = 0.f;

				if (this->currRect != this->endRect) {// NEXT FRAME
					this->currRect.left += this->width;
				} else { // RESET
					this->currRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currRect);
			}

			return this->done;
		}

		void reset() {
			this->timer = this->animSpeed;
			this->currRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	Animation* lastAnim;
	Animation* priorityAnim;

	std::map<std::string, Animation*> animations;


public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	const bool& isDone(const std::string key);


	void addAnim(const std::string key, float animSpeed,
		int startFrameX, int startFrameY,
		int framesX, int framesY,
		int width, int height);

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifierMax, const bool priority = false);
};

#endif 


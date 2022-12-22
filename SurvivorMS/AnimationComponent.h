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
			animSpeed(animSpeed), width(width), height(height) 
		{
			this->timer = 0.f;

			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currRect = this->startRect;
			this->endRect = sf::IntRect(framesX * width, framesY * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
			this->sprite.setScale(4, 4);
		}

		void play(const float& dt) {

			this->timer += 100.f * dt;

			if (this->timer >= this->animSpeed) {
				this->timer = 0.f;

				if (this->currRect != this->endRect) {
					this->currRect.left += this->width;
				} else {
					this->currRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currRect);
			}
		}

		void reset() {
			this->timer = 0.f;
			this->currRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;


public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	void addAnim(const std::string key, float animSpeed,
		int startFrameX, int startFrameY,
		int framesX, int framesY,
		int width, int height);

	//void startAnim(const std::string animation);
	//void pauseAnim(const std::string animation);
	//void restartAnim(const std::string animation);

	void play(const std::string key, const float& dt);
};

#endif 


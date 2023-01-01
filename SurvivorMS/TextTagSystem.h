#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

enum TAGTYPES { DEFAULT_TAG = 0, DAMAGE_TAG, EXPERIENCE_TAG };

class TextTagSystem {
private:

	class TextTag {
	private:
		sf::Text text;

		float dirX;
		float dirY;
		float lifeTime;
		float speed;

		float acceleration;
		sf::Vector2f velocity;

		int fadeValue;
		bool reverse;

	public:
		TextTag(sf::Font& font, std::string txt,
			float x, float y,
			float dirX, float dirY,
			sf::Color color, unsigned charSize,
			float lifeTime, bool reverse, float speed, 
			float acceleration, int fadeValue) {

			this->text.setFont(font);
			this->text.setPosition(x, y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(charSize);
			this->text.setString(txt);

			this->dirX = dirX;
			this->dirY = dirY;
			this->lifeTime = lifeTime;
			this->speed = speed;
			this->reverse = reverse;
			this->acceleration = acceleration;
			this->fadeValue = fadeValue;

			if (this->reverse) {
				this->velocity.x = this->dirX * this->speed;
				this->velocity.y = this->dirY * this->speed;
			}
		}

		TextTag(TextTag* tag, float x, float y, std::string txt) {

			this->text = tag->text;
			this->text.setString(txt);
			this->text.setPosition(x, y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
			this->reverse = tag->reverse;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			this->velocity = tag->velocity;
		}

		~TextTag() {

		}

		inline const bool canBeRemoved() const { return this->lifeTime <= 0.f; }


		void update(const float& dt) {

			if (this->lifeTime > 0.f) {

				this->lifeTime -= 100.f * dt;

				if (this->acceleration > 0.f) {

					if (this->reverse) {

						this->velocity.x -= this->dirX * this->acceleration * dt;
						this->velocity.y -= this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) < 0.f)
							this->velocity.x = this->dirX * this->speed;

						if (abs(this->velocity.y) < 0.f)
							this->velocity.y = this->dirY * this->speed;

					} else {

						this->velocity.x += this->dirX * this->acceleration * dt;
						this->velocity.y += this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) > this->speed)
							this->velocity.x = this->dirX * this->speed;

						if (abs(this->velocity.y) > this->speed)
							this->velocity.y = this->dirY * this->speed;
					}

					this->text.move(this->velocity * dt);
					
				} else {

					this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
				}

				if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue) {

					this->text.setFillColor(
						sf::Color(
							this->text.getFillColor().r,
							this->text.getFillColor().g,
							this->text.getFillColor().b,
							this->text.getFillColor().a - this->fadeValue
						)
					);
				}

			}
		}
		void render(sf::RenderTarget& target) {

			target.draw(this->text);

		}
	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	void initFonts(std::string fontFile);
	void initVariables();
	void initTagTemplates();

public:
	TextTagSystem(std::string fontFile);
	~TextTagSystem();

	void addTextTag(const unsigned tagType, const float x, const float y, const std::string txt, const std::string prefix, const std::string postfix);
	void addTextTag(const unsigned tagType, const float x, const float y, const int val, const std::string prefix, const std::string postfix);
	void addTextTag(const unsigned tagType, const float x, const float y, const float valF, const std::string prefix, const std::string postfix);
	void removeTextTag();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif // !TEXTTAGSYSTEM_H
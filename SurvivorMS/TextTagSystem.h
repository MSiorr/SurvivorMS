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

	public:
		TextTag(sf::Font& font, std::string txt,
			float x, float y,
			float dirX, float dirY,
			sf::Color color, unsigned charSize,
			float lifeTime, float speed) {

			this->text.setFont(font);
			this->text.setPosition(x, y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(charSize);
			this->text.setString(txt);

			this->dirX = dirX;
			this->dirY = dirY;
			this->lifeTime = lifeTime;
			this->speed = speed;
		}

		TextTag(TextTag* tag, float x, float y, std::string txt) {

			this->text = tag->text;
			this->text.setString(txt);
			this->text.setPosition(x, y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
		}

		~TextTag() {

		}

		inline const bool canBeRemoved() const { return this->lifeTime <= 0.f; }


		void update(const float& dt) {

			if (this->lifeTime > 0.f) {

				this->lifeTime -= 100.f * dt;

				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
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

	void addTextTag(const unsigned tagType, const float x, const float y, const std::string txt);
	void addTextTag(const unsigned tagType, const float x, const float y, const int val);
	void addTextTag(const unsigned tagType, const float x, const float y, const float valF);
	void removeTextTag();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif // !TEXTTAGSYSTEM_H
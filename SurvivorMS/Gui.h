#ifndef GUI_H
#define GUI_H

enum BUTTONSTATES {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {

	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm);

	class Button {
	private:
		short unsigned btnState;
		short unsigned id;

		bool graphicBtn;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Texture btnTexture;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string textOrPath, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, 
			sf::Color outlineHoverColor = sf::Color::Transparent, 
			sf::Color outlineActiveColor = sf::Color::Transparent,
			bool graphicBtn = false, short unsigned id = 0);
		virtual ~Button();

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		void setText(const std::string text);
		void setId(const short unsigned id);

		void update(const sf::Vector2i& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList {
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;

		gui::Button* activeElement;
		std::vector<gui::Button*> list;

		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, float fontSize, sf::Font& font, std::string list[], unsigned elementsCount, unsigned defaultIndex = 0);
		~DropDownList();

		const bool getKeytime();
		const unsigned short& getActiveElementID() const;

		void updateKeytime(const float& dt);

		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector {
	private:

		float keytime;
		float keytimeMax;

		float gridSize;
		bool active;

		bool hidden;
		gui::Button* hideBtn;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;



	public:
		TextureSelector(float x, float y, float width, float height,
			float gridSize, const sf::Texture* textureSheet,
			sf::Font& font, std::string text);
		~TextureSelector();

		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		void updateKeytime(const float& dt);

		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar {
	private:
		std::string barString;
		sf::Text text;

		float maxWidth;
		int maxValue;

		sf::RectangleShape back;
		sf::RectangleShape inner;

	public:
		ProgressBar(
			float x, float y, 
			float width, float height, 
			float _charSizeMultip, 
			int maxValue, sf::Color innerColor,
			sf::VideoMode& vm, sf::Font* font = NULL);
		~ProgressBar();

		void updateMaxVal(const float val);

		void update(const int currVal);
		void render(sf::RenderTarget& target);
	};
	
}

#endif 
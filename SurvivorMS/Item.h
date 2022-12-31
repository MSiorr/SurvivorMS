#ifndef ITEM_H
#define ITEM_H

class Item {
private:

protected:

	sf::Sprite sprite;

	bool weaponBool;
	bool toDestroy;

public:
	Item(bool weaponBool = false);
	virtual ~Item();

	const bool isWeapon() const;
	const bool isToDestroy() const;

	void setToDestroy(bool val);

	virtual const sf::FloatRect getGlobalBounds() const;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false) = 0;
};

#endif 
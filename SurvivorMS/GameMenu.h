#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "State.h"
#include "AnimationComponent.h"
#include "PlayerData.h"
#include "GameState.h"

class GameMenu :
    public State {
private:

    float mainTopPadding;

    int gold;

    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    sf::RectangleShape playerAvBg;
    sf::Texture playerAvTexture;
    sf::Sprite playerAv;
    AnimationComponent* playerAvAnimComp;

    sf::RectangleShape infoBox;
    sf::Text headerTxt;
    sf::Text infoTxt;
    sf::RectangleShape goldShapeBox;
    sf::Text costTxt;

    sf::Text goldTxt;
    sf::Texture goldTexture;
    sf::RectangleShape goldShapeTop;

    sf::Text dmgTxt;
    sf::Text hpTxt;

    PlayerData* playerData;
    bool buyActive;
    short activeItem;

    void initFonts();
    void initPlayerData(bool newGame);
    void initGold();
    void initKeyBinds();
    void initGuiItems();
    void initGui();
    void initPlayerAvatar();
    void initInfoBox();

public:
    GameMenu(StateData* stateData, bool newGame);
    ~GameMenu();

    void resetGUI();
    void changeActiveItem(short key);

    void updateInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updateInfoBox(const float& dt);
    void updateGold(const float& dt);
    void update(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void renderInfoBox(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};


#endif // !GAMEMENU_H




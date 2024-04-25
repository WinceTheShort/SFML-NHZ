//
// Created by wince on 2024. 04. 24..
//

#ifndef SFML_NHZ_DIFFICULLTYSTATE_H
#define SFML_NHZ_DIFFICULLTYSTATE_H

#include "State.h"
#include "GameState.h"


class DifficulltyState : public State{
private:
    sf::RectangleShape backgroundColor;
    sf::Font font;
    sf::Texture texture;
    sf::Sprite backgroundBorder;

    std::map<std::string, Difficulty*> difficulties;
    std::map<std::string, Button*> buttons;

    //Functions
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initDifficulty();

public:

    DifficulltyState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~DifficulltyState();

    //Functions
    void endState();


    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_DIFFICULLTYSTATE_H

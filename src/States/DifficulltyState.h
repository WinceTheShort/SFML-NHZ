//
// Created by wince on 2024. 04. 24..
//

#ifndef SFML_NHZ_DIFFICULLTYSTATE_H
#define SFML_NHZ_DIFFICULLTYSTATE_H

#include "CustomDiffState.h"


class DifficulltyState : public iButton{
private:
    sf::RectangleShape backgroundColor;
    sf::RectangleShape backgroundBorder;

    std::map<std::string, Difficulty*> difficulties;

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


    void handleInput(const float& dt) override;
    void handleButtons() override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};


#endif //SFML_NHZ_DIFFICULLTYSTATE_H

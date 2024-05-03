//
// Created by wince on 2024. 04. 27..
//

#ifndef SFML_NHZ_CUSTOMDIFFSTATE_H
#define SFML_NHZ_CUSTOMDIFFSTATE_H

#include "GameState.h"

class CustomState: public iButton, public iSlider{
private:
    sf::RectangleShape backgroundColor;
    sf::RectangleShape backgroundBorder;
    Difficulty* customDif;

    void initFonts();
    void initKeybinds();
    void initButtons();
    void initSliders();
public:
    CustomState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~CustomState();

    //Functions
    void endState();


    void handleInput(const float& dt);
    void handleButtons();
    void handleSliders();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_CUSTOMDIFFSTATE_H

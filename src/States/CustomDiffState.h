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

    void initFonts();       //Initializes fonts
    void initKeybinds();    //Initializes keybinds
    void initButtons();     //Initializes buttons
    void initSliders();     //Initializes sliders
public:
    CustomState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~CustomState();

    //Functions
    void endState();


    void handleInput(const float& dt);                  //Handles inputs, takes delta time
    void handleButtons();                               //Handles buttons
    void handleSliders();                               //Handles sliders
    void update(const float& dt);                       //updates the state, takes delta time
    void render(sf::RenderTarget* target = nullptr);    //Renders state elements, takes sf::RenderTarget*
};


#endif //SFML_NHZ_CUSTOMDIFFSTATE_H

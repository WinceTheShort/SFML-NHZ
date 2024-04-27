//
// Created by wince on 2024. 04. 27..
//

#ifndef SFML_NHZ_CUSTOMSTATE_H
#define SFML_NHZ_CUSTOMSTATE_H

#include "GameState.h"

class CustomState: public State{
private:
    sf::RectangleShape backgroundColor;
    sf::Font font;
    sf::Texture texture;
    sf::Sprite backgroundBorder;
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


    void updateInput(const float& dt);
    void updateButtons();
    void updateSliders();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_CUSTOMSTATE_H

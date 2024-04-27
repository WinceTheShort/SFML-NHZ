//
// Created by wince on 2024. 04. 21..
//

#ifndef SFML_NHZ_MAINMENUSTATE_H
#define SFML_NHZ_MAINMENUSTATE_H

#include "DifficulltyState.h"

class MainMenuState : public State{
private:
    //Variables
    sf::RectangleShape backgroundColor;
    sf::Texture background;
    sf::Sprite backgroundImage;
    sf::Font font;


    std::map<std::string, Button*> buttons;
    std::map<std::string, Slider*> sliders;

    //Functions
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void endState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_MAINMENUSTATE_H

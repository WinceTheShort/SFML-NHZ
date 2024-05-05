//
// Created by wince on 2024. 04. 21..
//

#ifndef SFML_NHZ_MAINMENUSTATE_H
#define SFML_NHZ_MAINMENUSTATE_H

#include "DifficulltyState.h"

class MainMenuState : public iButton{
private:
    //Variables
    sf::RectangleShape backgroundColor;
    sf::Texture background;
    sf::Sprite backgroundImage;

    //Functions
    void initFonts();       //Initializes fonts
    void initKeybinds();    //Initializes keybinds
    void initButtons();     //Initializes buttons
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void endState();        //Performs actions before quitting the state

    void handleInput(const float& dt);                  //Handles inputs, takes delta time
    void handleButtons();                               //Handles buttons
    void update(const float& dt);                       //updates the state, takes delta time
    void render(sf::RenderTarget* target = nullptr);    //Renders state elements, takes sf::RenderTarget*
};


#endif //SFML_NHZ_MAINMENUSTATE_H

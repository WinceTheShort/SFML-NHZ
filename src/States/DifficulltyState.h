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
    void initFonts();       //Initializes fonts
    void initKeybinds();    //Initializes keybinds
    void initButtons();     //Initializes buttons
    void initDifficulty();  //Loads difficulties from config

public:

    DifficulltyState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~DifficulltyState();

    //Functions
    void endState();
    void loadGame();                                            //Loads saved game

    void handleInput(const float& dt) override;                 //Handles inputs, takes delta time
    void handleButtons() override;                              //Handles buttons
    void update(const float& dt) override;                      //updates the state, takes delta time
    void render(sf::RenderTarget* target = nullptr) override;   //Renders state elements, takes sf::RenderTarget*
};


#endif //SFML_NHZ_DIFFICULLTYSTATE_H

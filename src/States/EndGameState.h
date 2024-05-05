//
// Created by wince on 2024. 04. 30..
//

#ifndef SFML_NHZ_ENDGAMESTATE_H
#define SFML_NHZ_ENDGAMESTATE_H

#include "../Board.h"

class EndGameState : public iButton{
private:
    sf::RectangleShape backgroundColor;
    bool win;


    void initFonts();       //Initializes fonts
    void initKeybinds();    //Initializes keybinds
    void initButtons();     //Initializes buttons
public:
    EndGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, bool win);
    virtual ~EndGameState();

    void endState();

    void handleInput(const float& dt);                  //Handles inputs, takes delta time
    void handleButtons();                               //Handles buttons
    void update(const float& dt);                       //updates the state, takes delta time
    void render(sf::RenderTarget* target = nullptr);    //Renders state elements, takes sf::RenderTarget*
};


#endif //SFML_NHZ_ENDGAMESTATE_H

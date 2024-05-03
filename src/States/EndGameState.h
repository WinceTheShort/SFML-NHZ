//
// Created by wince on 2024. 04. 30..
//

#ifndef SFML_NHZ_ENDGAMESTATE_H
#define SFML_NHZ_ENDGAMESTATE_H

#include "StateInterfaces.hpp"

class EndGameState : public iButton{
private:
    sf::RectangleShape backgroundColor;


    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    EndGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EndGameState();

    void endState();

    void handleInput(const float& dt);
    void handleButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_ENDGAMESTATE_H

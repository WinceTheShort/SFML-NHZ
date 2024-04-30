//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_GAMESTATE_H
#define SFML_NHZ_GAMESTATE_H

#include "StateInterfaces.hpp"


class GameState : public iButton{
private:
    //Variables
    sf::RectangleShape backgroundColor;
    int correctFlag, wrongFlag;
    Difficulty *currentDifficulty;
    sf::Font font;

    //Functions
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Difficulty *difficulty);
    virtual ~GameState();

    //Functions
    void endState();


    void updateInput(const float& dt);
    void handleButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_GAMESTATE_H

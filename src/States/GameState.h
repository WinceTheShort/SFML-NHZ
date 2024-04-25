//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_GAMESTATE_H
#define SFML_NHZ_GAMESTATE_H

#include "State.h"
#include "../Button.h"

struct Difficulty{
    int width, height, bombNum;
};

class GameState : public State{
private:
    //Variables
    int correctFlag, wrongFlag;
    Difficulty *currentDifficulty;
    std::map<std::string, Button*> buttons;
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
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_GAMESTATE_H

//
// Created by wince on 2024. 04. 21..
//

#ifndef SFML_NHZ_GAME_H
#define SFML_NHZ_GAME_H

#include "States/MainMenuState.h"

class Game {
private:
    //Variables
    sf::RenderWindow* window;
    sf::Event event;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSetings;
    bool fullscreen;

    sf::Clock dtClock;          //Delta time
    float dt;

    std::stack<State*> states;  //States stack

    std::map<std::string, int> supportedKeys;

    //Init
    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();

public:
    Game();
    virtual ~Game();

    //Functions
    void endApp();
        //update
    void updateDt();
    void updateSFMLEvents();
    void update();
        //Render
    void render();
        //GameLoop
    void run();
};


#endif //SFML_NHZ_GAME_H

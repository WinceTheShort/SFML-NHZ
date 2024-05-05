//
// Created by wince on 2024. 04. 21.
//

#ifndef SFML_NHZ_STATE_H
#define SFML_NHZ_STATE_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "../Button.h"
#include "../Slider.h"

class State {
protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    std::map<std::string, std::map<std::string, sf::Color>> colorThemes;
    std::string activeTheme;
    sf::Font font;

    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::vector<sf::Texture*> textures;

    void initColorThemes();                                         //Loads themes from config

    //Functions
    virtual void initKeybinds() = 0;                                //Initializes keybinds


public:

    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    bool getQuit() const;                                           //Returns quit bool

    virtual void checkForQuit();                                    //Checks quit bool

    virtual void endState() = 0;                                    //Performs actions before quitting the state
    virtual void updateMousePositions();                            //Updates mouse positions
    virtual void handleInput(const float& dt) = 0;                  //Handles inputs, takes delta time
    virtual void update(const float& dt) = 0;                       //updates the state, takes delta time
    virtual void render(sf::RenderTarget* target = nullptr) = 0;    //Renders state elements, takes sf::RenderTarget*

    //Debug: displays mouse cords
    virtual void renderDebug(sf::RenderTarget* target){
        std::stringstream ss;
        sf::Text mousePosText;
        sf::RectangleShape backdrop;
        sf::Font debugFont;

        debugFont.loadFromFile("../../src/Resources/minepixel.ttf");
        ss << "Screen: " << mousePosScreen.x << ", " << mousePosScreen.y << "\n" <<
        "Window: " << mousePosWindow.x << ", " << mousePosWindow.y << "\n" <<
        "View: " << mousePosView.x << ", " << mousePosView.y;
        mousePosText.setFont(font);
        mousePosText.setString(ss.str());
        mousePosText.setPosition(sf::Vector2f(20,20));
        mousePosText.setCharacterSize(15);
        mousePosText.setFillColor(sf::Color::Black);
        backdrop.setSize(sf::Vector2f(300,200));
        backdrop.setFillColor(sf::Color(255,255,255,100));

        target->draw(backdrop);
        target->draw(mousePosText);
    }
};


#endif //SFML_NHZ_STATE_H

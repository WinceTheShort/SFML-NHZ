//
// Created by wince on 2024. 04. 21..
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

    std::map<std::string, Button*> buttons;
    std::map<std::string, Slider*> sliders;

    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::vector<sf::Texture*> textures;

    void initColorThemes();

    //Functions
    virtual void initKeybinds() = 0;

public:

    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    bool getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;
    virtual void updateMousePositions();
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    void renderButtons(sf::RenderTarget *target);
    void renderSliders(sf::RenderTarget *target);
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //SFML_NHZ_STATE_H

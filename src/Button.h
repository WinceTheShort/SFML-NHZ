//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_BUTTON_H
#define SFML_NHZ_BUTTON_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class Button {
private:
    std::string buttonStateS;
    int buttonState;
    sf::RectangleShape shape;
    sf::RectangleShape shadow;
    sf::Font* font;
    sf::Text text;
    /*sf::Text textShadow;*/
    float shadowSize;

    std::map<std::string, sf::Color>* theme;

public:
    Button(float x, float y, float width, float height,float outlineThickness,
            sf::Font* font, std::string text, int fontSize,
           std::map<std::string, sf::Color>* theme, float shadowSize = 0);
    ~Button();

    //Accessors
    const bool isPressed() const;

    //Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

};


#endif //SFML_NHZ_BUTTON_H

//
// Created by wince on 2024. 04. 26..
//

#ifndef SFML_NHZ_SLIDER_H
#define SFML_NHZ_SLIDER_H

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


class Slider {
private:
    sf::RectangleShape area;
    sf::RectangleShape slider;
    sf::Font* font;
    sf::Text text;
    sf::Text valueDisplay;
    int value, min, max;
    std::stringstream ss;
    float sliderMaxX;

    std::map<std::string, sf::Color>* theme;
public:
    Slider(float x, float y, float width,
           sf::Font* font, std::string text, int fontSize,
           std::map<std::string, sf::Color>* theme,
           int min, int max, float scale = 1);
    ~Slider();

    int getValue();

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};


#endif //SFML_NHZ_SLIDER_H

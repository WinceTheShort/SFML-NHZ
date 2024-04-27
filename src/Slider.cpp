//
// Created by wince on 2024. 04. 26..
//

#include <cmath>
#include "Slider.h"

Slider::Slider(float x, float y, float width, sf::Font *font, std::string text, int fontSize,
               std::map<std::string, sf::Color> *theme, int min, int max, float scale) {
    this->theme = theme;
    this->font = font;
    this->min = min;
    this->max = max;
    value = min;

    area.setPosition(sf::Vector2f(x, y));
    area.setSize(sf::Vector2f(width, 10 * scale));
    area.setOutlineThickness(5);
    area.setOutlineColor(sf::Color::Black);
    area.setFillColor(theme->at("BtnIdle"));

    slider.setPosition(sf::Vector2f(x, y - (20 * scale - 10 * scale)/2));
    slider.setSize(sf::Vector2f(10*scale,20 * scale));
    slider.setOutlineColor(sf::Color::Black);
    slider.setOutlineThickness(5);
    sliderMaxX = x + width - 10 * scale;

    this->text.setFont(*font);
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(text);
    this->text.setPosition(sf::Vector2f(area.getPosition().x + area.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        slider.getPosition().y - this->text.getGlobalBounds().height - 10));
    valueDisplay.setFont(*font);
    valueDisplay.setCharacterSize(fontSize);
    valueDisplay.setFillColor(sf::Color::Black);
}

Slider::~Slider() {

}

int Slider::getValue() {
    return value;
}

void Slider::update(sf::Vector2f mousePos) {
    slider.setFillColor(sf::Color::White);
    if (slider.getGlobalBounds().contains(mousePos)){
        slider.setFillColor(theme->at("BtnIdle"));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            slider.setFillColor(theme->at("BtnHover"));
            if (mousePos.x - 5 > area.getPosition().x && mousePos.x < sliderMaxX + 5)
                slider.setPosition(mousePos.x - 5, slider.getPosition().y);
        }
    }

    value = std::round(min + (slider.getPosition().x - area.getPosition().x) / (sliderMaxX - area.getPosition().x) * (max - min));


    ss.str(std::string());
    ss << value;
    valueDisplay.setString(ss.str());
    this->valueDisplay.setPosition(sf::Vector2f(area.getPosition().x + area.getSize().x/2 - this->valueDisplay.getGlobalBounds().width/2,
                                        slider.getPosition().y + slider.getSize().y + 10));
}

void Slider::render(sf::RenderTarget *target) {
    target->draw(area);
    target->draw(slider);
    target->draw(text);
    target->draw(valueDisplay);;
}

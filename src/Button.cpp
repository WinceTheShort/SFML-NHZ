//
// Created by wince on 2024. 04. 22..
//

#include "Button.h"

Button::Button(float x, float y, float width, float height,float outlineThickness,
               sf::Font* font, std::string text, int fontSize,
               std::map<std::string, sf::Color>* theme, float shadowSize, float textShadowSize){
    this->buttonState = 0;
    this->buttonStateS = "BtnIdle";

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(outlineThickness);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(fontSize);


    this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));

    textShadow.setFont(*this->font);
    textShadow.setCharacterSize(fontSize);
    textShadow.setString(text);
    textShadow.setFillColor(theme->at("Shadow"));
    textShadow.setPosition(sf::Vector2f(this->text.getPosition().x + textShadowSize, this->text.getPosition().y + textShadowSize));

    this->shadowSize = shadowSize;
    if(this->shadowSize != 0){
        this->shadow.setSize(sf::Vector2f(width, height));
        this->shadow.setPosition(sf::Vector2f(x + shadowSize,y + shadowSize));
        this->shadow.setFillColor(theme->at("Shadow"));
        this->shadow.setOutlineColor(theme->at("Shadow"));
        this->shadow.setOutlineThickness(outlineThickness);
    }



    this->theme = theme;
}

Button::~Button() {

}

const bool Button::isPressed() const {
    if (this->buttonState == 2)
        return true;
    return false;
}



void Button::update(const sf::Vector2f mousePos) {
    if (this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonStateS = "BtnHover";
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonStateS = "BtnActive";
            this->buttonState = 1;
        }
    } else if (buttonState != 1){
        this->buttonStateS = "BtnIdle";
        this->buttonState = 0;
    }

    if (buttonState == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (this->shape.getGlobalBounds().contains(mousePos))
            this->buttonState = 2;
        else{
            this->buttonStateS = "BtnIdle";
            this->buttonState = 0;
        }
    }

    this->shape.setFillColor(this->theme->at(buttonStateS));
}

void Button::render(sf::RenderTarget *target) {
    if (this->shadowSize != 0){
        target->draw(this->shadow);
    }

    target->draw(this->shape);
    target->draw(this->textShadow);
    target->draw(this->text);
}


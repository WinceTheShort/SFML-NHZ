//
// Created by wince on 2024. 04. 21..
//

#include "State.h"

void State::initColorThemes(){
    this->activeTheme = "Grayscale";
    std::ifstream file("../../src/Config/Themes/GrayScale.txt.");

    this->colorThemes["Grayscale"];
    if (file.is_open()){        //Grayscale
        std::string Color;
        int r, g, b, a;
        while (file >> Color >> r >> g >> b >> a) {
            sf::Color color(r, g, b, a);
            this->colorThemes["Grayscale"][Color] = color;
        }
    }

}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) {
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->quit = false;
    this->initColorThemes();
}

State::~State() {

}

bool State::getQuit() const {
    return this->quit;
}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT"))))
        this->quit = true;
}

void State::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));


}

void State::renderButtons(sf::RenderTarget *target) {
    for(auto &it : this->buttons)
        it.second->render(target);
}

void State::renderSliders(sf::RenderTarget *target) {
    for(auto &it : this->sliders)
        it.second->render(target);
}

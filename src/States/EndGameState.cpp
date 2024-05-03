//
// Created by wince on 2024. 04. 30..
//

#include "EndGameState.h"

void EndGameState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void EndGameState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void EndGameState::initButtons() {

}

EndGameState::EndGameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,std::stack<State *> *states)
: State(window, supportedKeys, states){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

EndGameState::~EndGameState() {
    deleteButtons();
}

void EndGameState::endState() {

}

void EndGameState::handleInput(const float &dt) {
    this->checkForQuit();
}

void EndGameState::handleButtons() {

}

void EndGameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
}

void EndGameState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(backgroundColor);
    this->renderButtons(target);
}



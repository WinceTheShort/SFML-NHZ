//
// Created by wince on 2024. 04. 21..
//

#include "MainMenuState.h"

void MainMenuState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void MainMenuState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void MainMenuState::initButtons() {
    this->buttons["PLAY"] = new Button(690, 280, 540, 170, 20, &this->font, "PLAY",120, &this->colorThemes.at(activeTheme),10,6);
    this->buttons["SETTINGS"] = new Button(430, 510, 1060, 170, 20, &this->font, "SETTINGS",120, &this->colorThemes.at(activeTheme),10,6);
    this->buttons["SCORES"] = new Button(530, 740, 820, 170, 20, &this->font, "SCORES",120, &this->colorThemes.at(activeTheme),10,6);
    this->buttons["QUIT"] = new Button(835, 955, 250, 85, 10, &this->font, "QUIT",60, &this->colorThemes.at(activeTheme),5,3);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states)
: State(window, supportedKeys, states){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    this->backgroundColor.setSize(sf::Vector2f (window->getSize().x, window->getSize().y));
    this->backgroundColor.setFillColor(sf::Color(97, 97, 97, 255));

    this->background.loadFromFile("../../src/Resources/MenuBackground.png");
    this->backgroundImage.setTexture(background);

}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second;
    }
}

void MainMenuState::endState() {

}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();
}

void MainMenuState::updateButtons() { //Updates and handles buttons
    for(auto &it : this->buttons)
        it.second->update(this->mousePosView);

    if (this->buttons["QUIT"]->isPressed())
        this->quit = true;
    if (this->buttons["PLAY"]->isPressed()){
        this->states->push(new DifficulltyState(this->window, this->supportedKeys, this->states));
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;
    target->draw(this->backgroundColor);
    target->draw(this->backgroundImage);

    this->renderButtons(target);
}


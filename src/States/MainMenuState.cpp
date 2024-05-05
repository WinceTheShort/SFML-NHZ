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
    this->buttons["PLAY"] = new Button(690,280,540,170,20,10,&this->colorThemes.at(activeTheme), &this->font,"PLAY",120,6);
    this->buttons["SETTINGS"] = new Button(430,510,1060,170,20,10,&this->colorThemes.at(activeTheme), &this->font,"SETTINGS",120,6);
    this->buttons["SCORES"] = new Button(530,740,820,170,20,10,&this->colorThemes.at(activeTheme), &this->font,"SCORES",120,6);
    this->buttons["QUIT"] = new Button(835,955,250,85,10,5,&this->colorThemes.at(activeTheme),&this->font,"QUIT",60,3);
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
    deleteButtons();
}

void MainMenuState::endState() {

}

void MainMenuState::handleInput(const float &dt) {
    this->checkForQuit();
}

void MainMenuState::handleButtons() { //Updates and handles buttons
    if (this->buttons["QUIT"]->isPressed())
        this->quit = true;
    if (this->buttons["PLAY"]->isPressed()){
        this->states->push(new DifficulltyState(this->window, this->supportedKeys, this->states));
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(this->backgroundColor);
    target->draw(this->backgroundImage);

    this->renderButtons(target);

    //Debug
    renderDebug(target);
}


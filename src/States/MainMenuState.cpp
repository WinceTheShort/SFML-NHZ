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
    this->buttons["EXIT_STATE"] = new Button(100, 100, 150, 50, 10, &this->font, "QUIT",30, &this->colorThemes.at(activeTheme));
    this->buttons["GAME_STATE"] = new Button(100, 200, 150, 50, 10, &this->font, "GAME",30, &this->colorThemes.at(activeTheme));

    this->sliders["SLIDER"] = new Slider(300, 500, 150, &font, "Test1", 30, &this->colorThemes.at(activeTheme), 20, 40);
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

    auto it2 = this->sliders.begin();
    for (it2 = this->sliders.begin(); it2 != this->sliders.end(); ++it2){
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

    for(auto &it : this->sliders)
        it.second->update(this->mousePosView);

    if (this->buttons["EXIT_STATE"]->isPressed())
        this->quit = true;
    if (this->buttons["GAME_STATE"]->isPressed()){
        this->states->push(new DifficulltyState(this->window, this->supportedKeys, this->states));
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateInput(dt);
}

void MainMenuState::renderButtons(sf::RenderTarget *target) {
    for(auto &it : this->buttons)
        it.second->render(target);
    for(auto &it : this->sliders)
        it.second->render(target);
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;
    target->draw(this->backgroundColor);
    target->draw(this->backgroundImage);

    this->renderButtons(target);
}


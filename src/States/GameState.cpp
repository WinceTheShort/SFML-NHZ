//
// Created by wince on 2024. 04. 22..
//

#include "GameState.h"

void GameState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void GameState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void GameState::initButtons() {
    this->buttons["EXIT_STATE"] = new Button(100, 100, 150, 50, 10, &this->font, "BACK",12, &this->colorThemes.at(activeTheme));
    this->buttons["GAME_STATE"] = new Button(100, 200, 150, 50, 10, &this->font, "NEXT",10,  &this->colorThemes.at(activeTheme));
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states, Difficulty *difficulty)
: State(window, supportedKeys, states), currentDifficulty (difficulty) {
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    correctFlag = 0;
    wrongFlag = 0;

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

GameState::~GameState() {
    deleteButtons();
}

void GameState::endState() {

}

void GameState::updateInput(const float &dt) {
    this->checkForQuit();
}

void GameState::handleButtons() { //Updates and handles buttons
    if (this->buttons["EXIT_STATE"]->isPressed())
        this->quit = true;
    if (this->buttons["GAME_STATE"]->isPressed()){

    }
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateInput(dt);
}

void GameState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(backgroundColor);
    this->renderButtons(target);

    //Debug
    std::stringstream ss;
    ss << "Columns: " << currentDifficulty->columns << "\n"
    << "Rows: " << currentDifficulty->rows << "\n"
    << "Bombs: " << currentDifficulty->bombs;
    sf::Text text;
    text.setString(ss.str());
    text.setFont(font);
    text.setCharacterSize(20);
    target->draw(text);

}
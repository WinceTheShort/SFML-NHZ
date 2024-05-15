//
// Created by wince on 2024. 04. 24..
//

#include "DifficulltyState.h"

void DifficulltyState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void DifficulltyState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void DifficulltyState::initButtons() {
    this->buttons["EASY"] = new Button(760,70,400,100,20,10,&colorThemes.at(activeTheme),&font,"EASY",50);
    this->buttons["MEDIUM"] = new Button(760,240,400,100,20,10,&colorThemes.at(activeTheme),&font,"MEDIUM",50);
    this->buttons["HARD"] = new Button(760,410,400,100,20,10,&colorThemes.at(activeTheme),&font,"HARD",50);
    this->buttons["CUSTOM"] = new Button(760,580,400,100,20,10,&colorThemes.at(activeTheme),&font,"CUSTOM",50);
    this->buttons["LOAD"] = new Button(760,750,400,100,20,10,&colorThemes.at(activeTheme),&font,"LOAD",50);
    this->buttons["BACK"] = new Button(760,920,400,100,20,10,&colorThemes.at(activeTheme),&font,"BACK",50);


}

void DifficulltyState::initDifficulty() {
    std::ifstream file("../../src/Config/difficulty.ini");

    if (file.is_open()){        //Grayscale
        std::string Diff;
        int c, r, b;
        while (file >> Diff >> c >> r >> b) {
            this->difficulties[Diff] = new Difficulty(c,r,b);
        }
        difficulties["LOAD"] = new Difficulty(1,1,1);
    }
}

//Constructor
DifficulltyState::DifficulltyState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states)
: State(window, supportedKeys, states){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initDifficulty();

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    this->backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    this->backgroundBorder.setPosition(20, 20);
    this->backgroundBorder.setOutlineColor(sf::Color::Black);
    this->backgroundBorder.setOutlineThickness(20);
    this->backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));
}

//Destructor
DifficulltyState::~DifficulltyState() {
    deleteButtons();
    auto it2 = this->difficulties.begin();
    for (it2 = this->difficulties.begin(); it2 != this->difficulties.end(); ++it2){
        it2->second;
    }
}

void DifficulltyState::endState() {

}

void DifficulltyState::handleInput(const float &dt) {
    this->checkForQuit();
}

void DifficulltyState::handleButtons() { //Updates and handles buttons
        if (this->buttons["BACK"]->isPressed())
        this->quit = true;
    if (this->buttons["EASY"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("EASY")));
    }
    if (this->buttons["MEDIUM"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("MEDIUM")));
    }
    if (this->buttons["HARD"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("HARD")));
    }
    if (this->buttons["LOAD"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("LOAD"),true));
    }
    if (this->buttons["CUSTOM"]->isPressed()){
        this->states->push(new CustomState(this->window, this->supportedKeys, this->states));
    }
}

void DifficulltyState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
}

void DifficulltyState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(backgroundColor);
    target->draw(backgroundBorder);

    this->renderButtons(target);

    //Debug
    renderDebug(target);
}



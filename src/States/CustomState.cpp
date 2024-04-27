//
// Created by wince on 2024. 04. 27..
//

#include "CustomState.h"

void CustomState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void CustomState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void CustomState::initButtons() {
    this->buttons["BACK"] = new Button(40,40,150,70,10,&font,"BACK", 25, &colorThemes.at(activeTheme), 10);
    this->buttons["START"] = new Button(1730,40,150,70,10,&font,"START", 25, &colorThemes.at(activeTheme), 10);

}

void CustomState::initSliders() {
    this->sliders["COLUMNS"] = new Slider(860, 1000, 200, &font, "COLUMNS", 30, &colorThemes.at(activeTheme), 10, 100);
    this->sliders["ROWS"] = new Slider(610, 1000, 200, &font, "ROWS", 30, &colorThemes.at(activeTheme), 10, 100);
    this->sliders["BOMBS"] = new Slider(1110, 1000, 200, &font, "BOMBS", 30, &colorThemes.at(activeTheme), 10, 100);


}

CustomState::CustomState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                         std::stack<State*>* states)  : State(window, supportedKeys, states){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initSliders();

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    this->texture.loadFromFile("../../src/Resources/MenuBorder.png");
    this->backgroundBorder.setTexture(texture);
}

CustomState::~CustomState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second;
    }
    auto it2 = this->sliders.begin();
    for (it2 = this->sliders.begin(); it2 != this->sliders.end(); ++it2){
        it->second;
    }
    delete customDif;
}

void CustomState::endState() {

}

void CustomState::updateInput(const float &dt) {
    this->checkForQuit();
}

void CustomState::updateButtons() {
    for(auto &it : this->buttons)
        it.second->update(this->mousePosView);

    if (this->buttons["BACK"]->isPressed())
        this->quit = true;
    if (this->buttons["START"]->isPressed()){
        customDif = new Difficulty;
        customDif->width = sliders.at("COLUMNS")->getValue();
        customDif->height = sliders.at("ROWS")->getValue();
        customDif->bombNum = sliders.at("BOMBS")->getValue();
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, customDif));
    }
}

void CustomState::updateSliders() {
    for(auto &it : this->sliders)
        it.second->update(this->mousePosView);
}

void CustomState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateSliders();
    this->updateInput(dt);
}

void CustomState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;
    target->draw(backgroundColor);
    target->draw(backgroundBorder);

    renderButtons(target);
    renderSliders(target);
}

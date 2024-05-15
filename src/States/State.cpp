//
// Created by wince on 2024. 04. 21..
//

#include "State.h"

void State::initColorThemes(){
    using namespace std::filesystem;

    path directoryPath = "../../src/Config/Themes";

    this->activeTheme = "GRAYSCALE";

    if (exists(directoryPath)
        && is_directory(directoryPath)) {
        for (const auto& entry: directory_iterator(directoryPath)) {
            std::ifstream ifstream(entry.path());
            std::string Name, Color;
            int r, g, b, a;
            ifstream >> Name;
            while (ifstream >> Color >> r >> g >> b >> a) {
                sf::Color color(r,g,b,a);
                this->colorThemes[Name][Color] = color;
            }
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







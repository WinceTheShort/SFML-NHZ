//
// Created by wince on 2024. 04. 21.
//

#include "Game.h"
#include <fstream>

//Init

void Game::initVariables(){
    window = nullptr;
    fullscreen = false;
    dt = 0.f;

}

void Game::initWindow() {
    std::ifstream ifs("../../src/Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    //Def values
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if(ifs.is_open()){
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> this->fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    windowSetings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSetings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Default | sf::Style::Titlebar | sf::Style::Close, windowSetings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

    ifs.close();
}

void Game::initStates() {
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initKeys() {
    std::ifstream file("../../src/Config/supported_keys.ini");

    if (file.is_open()){
        std::string key;
        int key_value = 0;
        while (file >> key >> key_value)
            this->supportedKeys[key] = key_value;
    }
    file.close();
}



//Consturctors/Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty()){
        delete this->states.top();
        this->states.pop();
    }
}

//Functions

void Game::endApp() { //App end operations

}

void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->event)){
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvents();

    if(!this->states.empty()){
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Close app
    else {
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    //Render items
    if(!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}



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

void GameState::initBoard() {
    boardBackground.setSize(sf::Vector2f(gridSize*currentDifficulty->columns, gridSize*currentDifficulty->rows));
    boardBackground.setOutlineThickness(5);
    boardBackground.setOutlineColor(sf::Color::Black);
    view.setCenter(boardBackground.getSize().x/2, boardBackground.getSize().y/2);
    view.setSize(sf::Vector2f(boardBackground.getSize().x <= boardBackground.getSize().y ?
    (boardBackground.getSize().y + 55) * (16.f/9.f) : boardBackground.getSize().x + 55,
    boardBackground.getSize().x <= boardBackground.getSize().y ?
    boardBackground.getSize().y + 55 : (boardBackground.getSize().x + 55) / (16.f/9.f)));
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states, Difficulty *difficulty)
: State(window, supportedKeys, states), currentDifficulty (difficulty) {
    gridSize = 10;
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    correctFlag = 0;
    wrongFlag = 0;

    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
    viewSpeed = 200;
    isShiftPressed = false;

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    this->backgroundBorder.setPosition(20, 20);
    this->backgroundBorder.setOutlineColor(sf::Color::Black);
    this->backgroundBorder.setOutlineThickness(20);
    this->backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));

    this->initBoard();
}

GameState::~GameState() {
    deleteButtons();
}

void GameState::endState() {

}

bool GameState::checkWinCondition() {
    if (wrongFlag == 0 && correctFlag == currentDifficulty->bombs)
        return true;
    return false;
}

void GameState::handleInput(const float &dt) {
    this->checkForQuit();
    if (checkWinCondition())
        this->states->push(new EndGameState(this->window, this->supportedKeys, this->states));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !isShiftPressed){ //Shit for fast panning
        viewSpeed *= 2;
        isShiftPressed = true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && isShiftPressed){
        viewSpeed /= 2;
        isShiftPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
        view.move(-viewSpeed * dt,0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
        view.move(viewSpeed * dt,0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
        view.move(0.f,-viewSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Down
        view.move(0.f,viewSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && view.getSize().x > 200){
        view.setSize(view.getSize().x/1.01,view.getSize().y/1.01);
        viewSpeed /= 1.005;

    } //Zoom in

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && view.getSize().x < window->getSize().x){
        view.setSize(view.getSize().x*1.01,view.getSize().y*1.01);
        viewSpeed *= 1.005;
    } //Zoom out
}

void GameState::handleButtons() { //Updates and handles buttons
    if (this->buttons["EXIT_STATE"]->isPressed())
        this->quit = true;
    if (this->buttons["GAME_STATE"]->isPressed()){

    }
}

void GameState::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(mousePosWindow, view);
    mousePosGrid = sf::Vector2i(mousePosView.x/gridSize,mousePosView.y/gridSize);
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
}

void GameState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;
    target->draw(backgroundColor);

    //Set view
    window->setView(view);
    //Game Elements
    this->renderButtons(target);
    target->draw(boardBackground);

    test3.setSize(sf::Vector2f(5,5));
    test3.setPosition(window->getSize().x/2-2.5, window->getSize().y/2-2.5);
    test3.setFillColor(sf::Color::Black);

    //Reset view
    window->setView(window->getDefaultView());
    //Gui
    target->draw(test3);
    target->draw(backgroundBorder);
    //Debug
    renderDebug(target);
}


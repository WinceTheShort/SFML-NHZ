//
// Created by wince on 2024. 04. 22.
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
    this->buttons["EXIT_STATE"] = new Button(100,100,150,50,10,10,&this->colorThemes.at(activeTheme),&this->font,"BACK",12);
    this->buttons["GAME_STATE"] = new Button(100,200,150,50,10,10,&this->colorThemes.at(activeTheme),&this->font,"NEXT",10);
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states, Difficulty *difficulty, bool load)
: State(window, supportedKeys, states), currentDifficulty (difficulty) {
    gridSize = 12;
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    correctFlag = 0;
    wrongFlag = 0;
    win = false;

    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
    viewSpeed = 200;
    isShiftPressed = false;

    buttonSprites.loadFromFile("../../src/Resources/ButtonSprites.png");
    cellSprites.loadFromFile("../../src/Resources/CellSpriteSheet.png");

    this->backgroundColor.setFillColor(colorThemes.at(activeTheme).at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    this->backgroundBorder.setPosition(20, 20);
    this->backgroundBorder.setOutlineColor(sf::Color::Black);
    this->backgroundBorder.setOutlineThickness(20);
    this->backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));

    board = new Board(currentDifficulty, gridSize, &view, &cellSprites);
}

GameState::~GameState() {
    deleteButtons();
    delete board;
}

void GameState::endState() {

}

bool GameState::checkWinCondition() {
    if (wrongFlag == 0 && correctFlag == currentDifficulty->bombs){
        win = true;
        return true;
    } else if (board->gameOver())
        return true;
    return false;
}

void GameState::handleInput(const float &dt) {
    this->checkForQuit();
    if (checkWinCondition())
        this->states->push(new EndGameState(this->window, this->supportedKeys, this->states, win));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !isShiftPressed){ //Shift for fast panning
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && view.getSize().x > 200){ //Zoom in
        view.setSize(view.getSize().x/1.01,view.getSize().y/1.01);
        viewSpeed /= 1.005;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && view.getSize().x < window->getSize().x){ //Zoom out
        view.setSize(view.getSize().x*1.01,view.getSize().y*1.01);
        viewSpeed *= 1.005;
    }
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
    board->drawBoard(target);

    //Reset view
    window->setView(window->getDefaultView());
    //Gui
    target->draw(test3);
    target->draw(backgroundBorder);
    //Debug
    renderDebug(target);
}


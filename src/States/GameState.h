//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_GAMESTATE_H
#define SFML_NHZ_GAMESTATE_H

#include "EndGameState.h"


class GameState : public iButton{
private:
    //Variables
    sf::RectangleShape backgroundColor;
    sf::RectangleShape backgroundBorder;
    sf::Texture buttonSprites;
    sf::Texture cellSprites;


    sf::View view;
    float viewSpeed;
    bool isShiftPressed;

    sf::Vector2i mousePosGrid;
    float gridSize;

    Difficulty *currentDifficulty;
    Board* board;
    int correctFlag, wrongFlag;
    bool win;

    int bombCounter, clock;
    sf::Text bombCounterText, clockText;
    sf::RectangleShape bombCounterBackground, clockBackground;

    sf::RectangleShape test3;



    //Functions
    void initFonts();       //Initializes fonts
    void initKeybinds();    //Initializes keybinds
    void initButtons();     //Initializes buttons
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Difficulty *difficulty, bool load = false);
    virtual ~GameState();

    //Functions
    void endState();
    bool checkWinCondition();                           //Checks if all bombs are correctly flagged, true=yes false=no
    void saveGame();                                    //Saves current game to a save file
    void setQuit();                                     //Sets quit bool


    void handleInput(const float& dt);                  //Handles inputs, takes delta time
    void handleButtons();                               //Handles buttons
    void updateMousePositions();                        //Updates mouse positions
    void updateClock(const float& dt);                  //Updates clock, takes delta time
    void updateBombCounter();                           //Updates bomb counter
    void update(const float& dt);                       //updates the state, takes delta time
    void render(sf::RenderTarget* target = nullptr);    //Renders state elements, takes sf::RenderTarget*

    void renderDebug(sf::RenderTarget* target){
        std::stringstream ss;
        sf::Text mousePosText;
        sf::RectangleShape backdrop;
        sf::Font debugFont;

        debugFont.loadFromFile("../../src/Resources/minepixel.ttf");
        ss << "Screen: " << mousePosScreen.x << ", " << mousePosScreen.y << "\n" <<
           "Window: " << mousePosWindow.x << ", " << mousePosWindow.y << "\n" <<
           "View: " << mousePosView.x << ", " << mousePosView.y << "\n" <<
           "Grid: " << mousePosGrid.x << ", " << mousePosGrid.y << "\n" <<
           "View size: " << view.getSize().x << ", " << view.getSize().y << "\n" <<
           "View speed:" << viewSpeed << "\n" <<
           "Columns: " << currentDifficulty->columns << "\n" <<
           "Rows: " << currentDifficulty->rows << "\n" <<
           "Bombs: " << currentDifficulty->bombs;
        mousePosText.setFont(font);
        mousePosText.setString(ss.str());
        mousePosText.setPosition(sf::Vector2f(20,20));
        mousePosText.setCharacterSize(15);
        mousePosText.setFillColor(sf::Color::Black);
        backdrop.setSize(sf::Vector2f(300,200));
        backdrop.setFillColor(sf::Color(255,255,255,100));

        target->draw(backdrop);
        target->draw(mousePosText);
    }     //Renders debug panel
};


#endif //SFML_NHZ_GAMESTATE_H

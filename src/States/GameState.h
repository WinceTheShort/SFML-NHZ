//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_GAMESTATE_H
#define SFML_NHZ_GAMESTATE_H

#include "EndGameState.h"


class GameState : public iButton{
private:
    //Variables
    sf::View view;
    float viewSpeed;
    bool isShiftPressed;
    sf::Vector2i mousePosGrid;
    float gridSize;
    sf::RectangleShape backgroundColor;
    int correctFlag, wrongFlag;
    Difficulty *currentDifficulty;
    sf::RectangleShape boardBackground;
    sf::RectangleShape backgroundBorder;
    sf::RectangleShape test3;



    //Functions
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initBoard();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, Difficulty *difficulty);
    virtual ~GameState();

    //Functions
    void endState();
    bool checkWinCondition();


    void handleInput(const float& dt);
    void handleButtons();
    void updateMousePositions();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

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
    }
};


#endif //SFML_NHZ_GAMESTATE_H

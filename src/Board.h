//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_BOARD_H
#define SFML_NHZ_BOARD_H

#include "Cell.h"

class Cell;

class Board {
private:
    Difficulty* diff;
    sf::RectangleShape boardBackground;
    sf::Texture *cellSprites;
    int gridSize, goodFlag, badFlag;
    sf::View* view;
    bool gameOverBool;

    Cell*** boardCells; //Stores cells

    void initBoard();   //initializes board
    void setBoard();    //sets cell values
public:
    Board(Difficulty* diff, int gridSize, sf::View* view, sf::Texture* cellSprites);
    ~Board();

    int getRemainigFlagNum(); //returns remaining flag num
    bool gameOver(){return gameOverBool;}  //returns game over bool
    void drawBoard(sf::RenderTarget* target);   //renders the board, takes sf::RenderTarget*
};


#endif //SFML_NHZ_BOARD_H

//
// Created by wince on 2024. 05. 05..
//

#include "Board.h"

void Board::initBoard() {
    boardBackground.setSize(sf::Vector2f(gridSize*diff->columns, gridSize*diff->rows));
    boardBackground.setOutlineThickness(5);
    boardBackground.setOutlineColor(sf::Color::Black);
    view->setCenter(boardBackground.getSize().x/2, boardBackground.getSize().y/2);
    view->setSize(sf::Vector2f(boardBackground.getSize().x <= boardBackground.getSize().y ?
                              (boardBackground.getSize().y + 55) * (16.f/9.f) : boardBackground.getSize().x + 55,
                              boardBackground.getSize().x <= boardBackground.getSize().y ?
                              boardBackground.getSize().y + 55 : (boardBackground.getSize().x + 55) / (16.f/9.f)));
    boardCells = new Cell**[diff->columns];
    for (int i = 0; i < diff->columns; ++i) {
        boardCells[i] = new Cell*[diff->rows];
    }
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            boardCells[i][j] = nullptr;
        }
    }

}

void Board::setBoard() {

}

Board::Board(Difficulty* diff, int gridSize, sf::View* view, sf::Texture* cellSprites)
: diff(diff), gridSize(gridSize), view(view), cellSprites(cellSprites){
    goodFlag=0;
    badFlag=0;
    gameOverBool = false;
    initBoard();
    setBoard();
}

Board::~Board() {
    for (int i = 0; i < diff->columns; ++i) {
        delete[] boardCells[i];
    }
    delete[] boardCells;
}

void Board::drawBoard(sf::RenderTarget *target) {
    target->draw(boardBackground);
}

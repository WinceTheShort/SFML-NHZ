//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_CELL_H
#define SFML_NHZ_CELL_H

#include "States/StateInterfaces.hpp"
#include "Board.h"

class Board;

class Cell {
protected:
    sf::RectangleShape shape;
    sf::Texture* spriteSheet;
    int type;
    bool revealed, flagged, satisfied;

    void initCell();    //initializes the cell
public:
    Cell(sf::Texture* spriteSheet, sf::Vector2f pos, int gridSize);

    void changeSprite(int spriteI); //Changes tiles sprite, takes the index of sprite
    void revealSurroundings(Board* board);  //reveals the cells surroundings
    virtual void reveal(Board* board);  //reveals the cell
    virtual void flag(Board* board);    //handles flag numbers
};

class BombCell: public Cell{
private:
public:
    BombCell(sf::Texture* spriteSheet, sf::Vector2f pos, int gridSize);
    ~BombCell();

    void reveal(Board* board);
    void flag(Board* board);
};

class ZeroCell: public Cell {
private:
public:
    ZeroCell(sf::Texture* spriteSheet, sf::Vector2f pos, int gridSize);
    ~ZeroCell();

    void reveal(Board* board);
    void flag(Board* board);
};

class NumCell: public Cell {
private:
    int value;
public:
    NumCell(sf::Texture* spriteSheet, sf::Vector2f pos, int gridSize);
    ~NumCell();

    void reveal(Board* board);
    void flag(Board* board);
};


#endif //SFML_NHZ_CELL_H

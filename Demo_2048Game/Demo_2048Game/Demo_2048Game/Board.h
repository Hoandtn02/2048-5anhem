#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "Tile.h"
using namespace std;
class Board {
protected:
    int size;
    std::vector<std::vector<Tile*>> tiles;
    bool useLetters; // Biến để lưu chế độ hiển thị (số hoặc chữ)

    static void setColor(int color); // Static function
    void rotateBoard();

public:
    Board(int s, bool useLetters);
    virtual ~Board();
    virtual void addRandomTile();
    virtual void display() const;
    virtual bool moveLeft();
    virtual bool moveRight();
    virtual bool moveUp();
    virtual bool moveDown();
    virtual bool canMove() const;
    bool isWinningCondition() const;
    std::vector<std::pair<int, int>> getEmptyPositions() const;
    std::vector<std::vector<int>> getTileValues() const;
    void setTileValue(int row, int col, int value);
    bool has2048() const;
};

class Board4x4 : public Board {
public:
    Board4x4(bool useLetters) : Board(4, useLetters) {}
};

class Board5x5 : public Board {
public:
    Board5x5(bool useLetters) : Board(5, useLetters) {}
};

class Board6x6 : public Board {
public:
    Board6x6(bool useLetters) : Board(6, useLetters) {}
};

#endif // BOARD_H

#include "Board.h"
#include <iostream>
#include <iomanip>
#include <Windows.h> // Thư viện này để sử dụng SetConsoleTextAttribute và GetConsoleScreenBufferInfo
using namespace std;

Board::Board(int s, bool useLetters) : size(s), useLetters(useLetters), tiles(s, vector<Tile*>(s)) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tiles[i][j] = new NumberTile();
        }
    }
    addRandomTile();
    addRandomTile();
}

Board::~Board() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            delete tiles[i][j];
        }
    }
}

void Board::addRandomTile() {
    vector<pair<int, int>> emptyPositions;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tiles[i][j]->isEmpty()) {
                emptyPositions.push_back({ i, j });
            }
        }
    }
    if (!emptyPositions.empty()) {
        int idx = rand() % emptyPositions.size();
        int value = (rand() % 2 + 1) * 2;
        tiles[emptyPositions[idx].first][emptyPositions[idx].second]->setValue(value);
    }
}

void Board::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Board::display() const {
    system("cls");

    // Get console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate board width and left padding for centering
    const int cellWidth = 7; // Cell width including padding
    const int cellHeight = 3; // Cell height including padding
    const int boardWidth = size * (cellWidth + 1) + 1;
    const int leftPadding = (consoleWidth - boardWidth) / 2;

    // Adjust left padding if it's negative
    int leftPaddingAdjusted;
    if (leftPadding > 0) {
        leftPaddingAdjusted = leftPadding;
    }
    else {
        leftPaddingAdjusted = 0;
    }

    // Border characters
    const string horizontalBorder = "=======";
    const char verticalBorder = '|';

    cout << "\n" << string(leftPaddingAdjusted, ' ') << "2048 Game\n\n";

    // Print top border
    cout << string(leftPaddingAdjusted, ' ') << "+";
    for (int j = 0; j < size; ++j) {
        cout << horizontalBorder << "+";
    }
    cout << "\n";

    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < cellHeight; ++k) {
            cout << string(leftPaddingAdjusted, ' ') << verticalBorder;
            for (int j = 0; j < size; ++j) {
                if (k == cellHeight / 2) {
                    // Print the value in the middle row of the cell
                    if (tiles[i][j]->isEmpty()) {
                        setColor(8); // Grey color for empty cells
                        cout << setw(cellWidth) << " ";
                    }
                    else {
                        switch (tiles[i][j]->getValue()) {
                        case 2: setColor(9); break;   // Blue
                        case 4: setColor(10); break;  // Green
                        case 8: setColor(11); break;  // Cyan
                        case 16: setColor(12); break; // Red
                        case 32: setColor(13); break; // Magenta
                        case 64: setColor(14); break; // Yellow
                        case 128: setColor(15); break; // White
                        case 256: setColor(16); break; // Cyan
                        case 512: setColor(17); break; // Magenta
                        case 1024: setColor(18); break; // Yellow
                        case 2048: setColor(19); break; // Red
                        default: setColor(7); break;   // Default color
                        }
                        string valueString = tiles[i][j]->getDisplayValue(useLetters);
                        int valueWidth = valueString.length();
                        int padding = (cellWidth - valueWidth) / 2;
                        cout << string(padding, ' ') << valueString << string(cellWidth - padding - valueWidth, ' ');
                    }
                }
                else {
                    // Print empty rows
                    cout << setw(cellWidth) << " ";
                }
                setColor(7); // Reset to default color
                cout << verticalBorder;
            }
            cout << "\n";
        }
        // Print horizontal border
        cout << string(leftPaddingAdjusted, ' ') << "+";
        for (int j = 0; j < size; ++j) {
            cout << horizontalBorder << "+";
        }
        cout << "\n";
    }
}



bool Board::moveLeft() {
    bool moved = false;
    for (int i = 0; i < size; ++i) {
        int lastMergePosition = -1;
        for (int j = 1; j < size; ++j) {
            if (!tiles[i][j]->isEmpty()) {
                int k = j;
                while (k > 0 && tiles[i][k - 1]->isEmpty()) {
                    tiles[i][k - 1]->setValue(tiles[i][k]->getValue());
                    tiles[i][k]->setValue(0);
                    k--;
                    moved = true;
                }
                if (k > 0 && tiles[i][k - 1]->canCombine(*tiles[i][k]) && lastMergePosition != k - 1) {
                    tiles[i][k - 1]->combine(*tiles[i][k]);
                    lastMergePosition = k - 1;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

void Board::rotateBoard() {
    vector<vector<Tile*>> newTiles(size, vector<Tile*>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newTiles[j][size - i - 1] = tiles[i][j];
        }
    }
    tiles = newTiles;
}

bool Board::moveRight() {
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    return moved;
}

bool Board::moveUp() {
    rotateBoard();
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    return moved;
}

bool Board::moveDown() {
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    rotateBoard();
    return moved;
}

bool Board::canMove() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tiles[i][j]->isEmpty()) return true;
            if (j < size - 1 && tiles[i][j]->canCombine(*tiles[i][j + 1])) return true;
            if (i < size - 1 && tiles[i][j]->canCombine(*tiles[i + 1][j])) return true;
        }
    }
    return false;
}

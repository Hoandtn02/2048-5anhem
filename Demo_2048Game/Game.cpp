#include "Game.h"
#include <conio.h>
#include <iostream>
using namespace std;

Game::Game() : board(nullptr), currentSize(4), useLetters(false) {
    selectGameMode();
    selectBoardSize();
}

Game::~Game() {
    delete board;
}

void Game::selectGameMode() {
    cout << "Select game mode by pressing the corresponding key:\n";
    cout << "1. Numbers\n";
    cout << "2. Letters\n";
    cout << "Press the corresponding key (1/2): ";

    while (true) {
        int ch = _getch();
        switch (ch) {
        case '1':
            useLetters = false;
            return;
        case '2':
            useLetters = true;
            return;
        default:
            cout << "Invalid choice. Please press 1 or 2: ";
            break;
        }
    }
}

void Game::selectBoardSize() {
    if (board != nullptr) {
        delete board;
    }

    cout << "Select board size by pressing the corresponding key:\n";
    cout << "1. 4x4\n";
    cout << "2. 5x5\n";
    cout << "3. 6x6\n";
    cout << "Press the corresponding key (1/2/3): ";

    while (true) {
        int ch = _getch();
        switch (ch) {
        case '1':
            currentSize = 4;
            board = new Board4x4(useLetters);
            return;
        case '2':
            currentSize = 5;
            board = new Board5x5(useLetters);
            return;
        case '3':
            currentSize = 6;
            board = new Board6x6(useLetters);
            return;
        default:
            cout << "Invalid choice. Please press 1, 2, or 3: ";
            break;
        }
    }
}

bool Game::isGameOver() const {
    return !board->canMove();
}

void Game::restartGame() {
    delete board; // Xóa bảng cũ
    switch (currentSize) {
    case 4:
        board = new Board4x4(useLetters);
        break;
    case 5:
        board = new Board5x5(useLetters);
        break;
    case 6:
        board = new Board6x6(useLetters);
        break;
    default:
        board = new Board4x4(useLetters); // Default to 4x4 if size is unknown
        break;
    }
}

void Game::play() {
    while (true) {
        board->display();

        // Check if game is over
        if (isGameOver()) {
            cout << "\nGame Over!\n";
            cout << "Press 'R' to restart or 'Q' to quit.\n";
        }
        else {
            cout << "Press 'M' to return to menu.\n";
        }

        int ch = _getch();
        bool moved = false;
        if (ch == 75) { // Left arrow key
            moved = board->moveLeft();
        }
        else if (ch == 77) { // Right arrow key
            moved = board->moveRight();
        }
        else if (ch == 72) { // Up arrow key
            moved = board->moveUp();
        }
        else if (ch == 80) { // Down arrow key
            moved = board->moveDown();
        }
        else if (ch == 'M' || ch == 'm') { // 'M' to return to menu
            selectGameMode(); // Chọn chế độ chơi
            selectBoardSize();
        }
        else if (ch == 'R' || ch == 'r') { // 'R' to restart game
            restartGame(); // Khởi động lại trò chơi với kích thước hiện tại
            continue; // Bắt đầu trò chơi mới
        }
        else if (ch == 'Q' || ch == 'q') { // 'Q' to quit game
            break;
        }

        if (moved) {
            board->addRandomTile();
        }
    }
}

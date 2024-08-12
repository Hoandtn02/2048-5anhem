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
        cout << "Press 'M' to return to menu\n";
        // Kiểm tra nếu người chơi thắng
        if (board->has2048()) {
            
            cout << "Press 'R' to restart or 'Q' to exit.\n";
            int ch = _getch();
            if (ch == 'R' || ch == 'r') {
                restartGame();
                continue;
            }
            else if (ch == 'Q' || ch == 'q') {
                break;
            }
            // Tiếp tục hiển thị thông báo cho đến khi nhấn 'R' hoặc 'Q'
            while (true) {
                ch = _getch();
                if (ch == 'R' || ch == 'r') {
                    restartGame();
                    break;
                }
                else if (ch == 'Q' || ch == 'q') {
                    return; // Thoát trò chơi
                }
            }
        }

        // Kiểm tra nếu trò chơi đã kết thúc
        if (isGameOver()) {
            cout << "\nGame Over!\n";
            cout << "Press 'R' to restart or 'Q' to exit.\n";
            int ch = _getch();
            if (ch == 'R' || ch == 'r') {
                restartGame();
                continue;
            }
            else if (ch == 'Q' || ch == 'q') {
                break;
            }
            continue;
        }

        int ch = _getch();
        bool moved = false;
        if (ch == 75) { // Phím mũi tên trái
            moved = board->moveLeft();
        }
        else if (ch == 77) { // Phím mũi tên phải
            moved = board->moveRight();
        }
        else if (ch == 72) { // Phím mũi tên lên
            moved = board->moveUp();
        }
        else if (ch == 80) { // Phím mũi tên xuống
            moved = board->moveDown();
        }
        else if (ch == 'M' || ch == 'm') { // 'M' để quay lại menu
            selectGameMode();
            selectBoardSize();
        }
        else if (ch == 'R' || ch == 'r') { // 'R' để khởi động lại trò chơi
            restartGame();
            continue;
        }
        else if (ch == 'Q' || ch == 'q') { // 'Q' để thoát trò chơi
            break;
        }
        else if (ch == 'C' || ch == 'c') { // 'C' để gian lận và đặt ô thành 2048
            auto emptyPositions = board->getEmptyPositions();
            if (!emptyPositions.empty()) {
                int idx = rand() % emptyPositions.size();
                board->setTileValue(emptyPositions[idx].first, emptyPositions[idx].second, 2048);
            }
        }

        if (moved) {
            board->addRandomTile();
        }
    }
}


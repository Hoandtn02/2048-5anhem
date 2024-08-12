#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
private:
    Board* board;
    int currentSize; // Lưu kích thước hiện tại
    bool useLetters; // Lưu chế độ chơi (số hoặc chữ)
    void selectBoardSize();
    void selectGameMode(); // Thêm khai báo hàm selectGameMode
    void restartGame(); // Thêm khai báo hàm restartGame
    bool isGameOver() const;

public:
    Game();
    ~Game();
    void play();
};

#endif // GAME_H

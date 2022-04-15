#pragma once

#include "cinder/gl/gl.h"
#include "board.h"
#include "player.h"

namespace fillergame {

class Game {
  private:
    Board board_;
    Player player1_;
    Player player2_;

    int tiles_left_;

    int margin_ = 50;
    int window_width_ = 800;
    int window_height_ = 800;

  public:
    Game(const int window_width, const int window_height, const int margin, const Board& board,
         const Player& player1, const Player& player2);

    void Display() const;

    void UpdateBoard();

    void RunGame();

    bool GameOver();
};

}
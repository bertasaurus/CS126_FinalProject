#pragma once

#include "board.h"
#include "player.h"

namespace fillergame {

class Game {
  private:
    Board board_;
    Player player1_;
    Player player2_;

  public:
    void Display() const;
};

}
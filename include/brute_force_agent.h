#pragma once

#include "player.h"

namespace fillergame {

class BruteForceAgent : public Player {
  private:
    int recursion_depth_;

    int player_idx_;

    /**
     * Evaluates the expected score of a specific move using a brute force algorithm to calculate
     * a number of moves in advance
     * @param board
     * @param depth
     * @param color
     * @param turn
     * @return
     */
    float EvaluateMove(const Board& board, const int depth, char* color, const int turn) const;

  public:
    BruteForceAgent(int player_idx, int recursion_depth);

    char* GetMove(const Board& board) const override;

    bool ShouldGetManualInput() const override;
  };

}
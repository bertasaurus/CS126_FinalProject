#pragma once

#include "player.h"

namespace fillergame {

class MonteCarloAgent : public Player {
  private:
    int recursion_depth_;
    int player_idx_;

    float EvaluateMove(const Board& board, const int depth, char* color, const int turn) const;

  public:
    MonteCarloAgent(int player_idx, int recursion_depth);

    char* GetMove(const Board& board) const override;

    bool ShouldGetManualInput() const override;
  };

}
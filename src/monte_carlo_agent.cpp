#pragma once

#include "monte_carlo_agent.h"

namespace fillergame {
  MonteCarloAgent::MonteCarloAgent(int player_idx, int recursion_depth)
      : player_idx_(player_idx), recursion_depth_(recursion_depth) {}

  char* MonteCarloAgent::GetMove(const Board& board) const {
    float best = 0;
    char* best_move;

    for (char* color : board.GetColors()) {
      float ev = EvaluateMove(board, recursion_depth_, color, player_idx_);
      if (ev > best) {
        best = ev;
        best_move = color;
      }
    }

    return best_move;
  }

  bool MonteCarloAgent::ShouldGetManualInput() const {
    return false;
  }

  float MonteCarloAgent::EvaluateMove(const Board &board, const int depth, char *color, const int turn) const {
    Board board_cpy(board);

    board_cpy.UpdateBoard(turn, color);

    if (depth == 0) {
      return board_cpy.GetPlayerScore(player_idx_);
    }

    float sum = 0;
    for (char* move : board.GetColors()) {
      sum = sum + EvaluateMove(board_cpy, depth - 1, move, turn % 2 + 1);
    }

    return sum / (float)board.GetColors().size();
  }

}
#pragma once

#include "brute_force_agent.h"

namespace fillergame {
  BruteForceAgent::BruteForceAgent(int player_idx, int recursion_depth)
      : player_idx_(player_idx), recursion_depth_(recursion_depth) {}

  char* BruteForceAgent::GetMove(const Board& board) const {
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

  bool BruteForceAgent::ShouldGetManualInput() const {
    return false;
  }

  float BruteForceAgent::EvaluateMove(const Board &board, const int depth, char *color, const int turn) const {
    Board board_cpy(board);

    board_cpy.UpdateBoard(turn, color);

    if (depth == 0) {
      return board_cpy.GetPlayerScore(player_idx_);
    }

    float best = 0;
    for (char* move : board.GetColors()) {
      float ev = EvaluateMove(board_cpy, depth - 1, move, turn % 2 + 1);
      if (ev > best) {
        best = ev;
      }
    }

    return best;
  }

}
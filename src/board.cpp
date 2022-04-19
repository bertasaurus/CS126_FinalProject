#pragma once

#include "board.h"
#include <ctime>
#include <iostream>

namespace fillergame {

Board::Board(const int width, const int height, const std::vector<char*>& colors)
      : width_(width), height_(height), colors_(colors), board_(width, height),
        tile_owner_(width, height), tiles_left_(width * height - 2) {
  GenerateColors();
  tile_owner_.set(0, height - 1, 1);
  tile_owner_.set(width - 1, 0, 2);
}

void Board::GenerateColors() {
  srand(time(NULL));
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      int idx = rand() % colors_.size();
      board_.set(i, j, colors_[idx]);
    }
  }
}

void Board::ClaimTile(const int player_idx, char *&color, const int a, const int b) {
  if (tile_owner_.at(a, b) != 0) {
    return;
  }

  if ((a > 0 && player_idx == tile_owner_.at(a - 1, b) && strcmp(board_.at(a, b), color) == 0)
      || (a < width_ - 1 && player_idx == tile_owner_.at(a + 1, b) && strcmp(board_.at(a, b), color) == 0)
      || (b > 0 && player_idx == tile_owner_.at(a, b - 1) && strcmp(board_.at(a, b), color) == 0)
      || (b < height_ - 1 && player_idx == tile_owner_.at(a, b + 1) && strcmp(board_.at(a, b), color) == 0)){
    tile_owner_.set(a, b, player_idx);
    tiles_left_--;
  }

}

void Board::ApplyMove(const int player_idx, char *&color) {
  int tmp = tiles_left_;
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      ClaimTile(player_idx, color, i, j);
    }
  }

  if (tmp != tiles_left_) {
    ApplyMove(player_idx, color);
  }
}

void Board::UpdateBoard(const int player_idx, char *&color) {
  ApplyMove(player_idx, color);

  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (tile_owner_.at(i, j) == player_idx) {
        board_.set(i, j, color);
      }
    }
  }


}

char* Board::GetTileColor(const int a, const int b) const {
  return board_.at(a, b);
}

int Board::GetWidth() const {
  return width_;
}

int Board::GetHeight() const {
  return height_;
}

int Board::GetGameWinner() const {
  if (tiles_left_ != 0) {
    return 0;
  }

  int player_1_score = GetPlayerScore(1);
  int player_2_score = GetPlayerScore(2);

  if (player_1_score > player_2_score) {
    return 1;
  }

  if (player_2_score > player_1_score) {
    return 2;
  }

  return 3;
}

int Board::GetPlayerScore(int player_idx) const {
  int count = 0;
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (tile_owner_.at(i, j) == player_idx) {
        count++;
      }
    }
  }
  return count;
}

}
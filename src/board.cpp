#pragma once

#include "board.h"

namespace fillergame {

Board::Board(const int width, const int height, const std::vector<char*>& colors)
      : width_(width), height_(height), colors_(colors), board_(width, height), tile_owner_(width, height) {
  GenerateColors();
}

void Board::GenerateColors() {
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      int idx = rand() % colors_.size();
      board_.set(width_, height_, colors_[idx]);
    }
  }
}

std::vector<glm::vec2> Board::GetAdjacentTiles(const int player_idx, char *&color) {
  std::vector<glm::vec2> adjacent_tiles;

  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (IsAdjacentToPlayer(player_idx, color, i, j)) {
        adjacent_tiles.push_back(glm::vec2(i, j));
      }
    }
  }

  return adjacent_tiles;
}

bool Board::IsAdjacentToPlayer(const int player_idx, char *&color, const int a, const int b) {
  if (a > 0 && player_idx == tile_owner_.at(a - 1, b) && strcmp(board_.at(a - 1, b), color) == 0) {
    return true;
  }

  if (a < width_ - 1 && player_idx == tile_owner_.at(a + 1, b) && strcmp(board_.at(a + 1, b), color) == 0) {
    return true;
  }

  if (b > 0 && player_idx == tile_owner_.at(a, b - 1) && strcmp(board_.at(a, b - 1), color) == 0) {
    return true;
  }

  if (b < height_ - 1 && player_idx == tile_owner_.at(a, b + 1) && strcmp(board_.at(a, b + 1), color) == 0) {
    return true;
  }

  return false;
}

int Board::UpdateBoard(const int player_idx, char *&color) {
  std::vector<glm::vec2> adjacent_tiles = GetAdjacentTiles(player_idx, color);

  for (const glm::vec2& tile : adjacent_tiles) {
    tile_owner_.set(tile.x, tile.y, player_idx);
  }

  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (tile_owner_.at(i, j) == player_idx) {
        board_.set(i, j, color);
      }
    }
  }

  return ((int) adjacent_tiles.size());
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

}
#pragma once

#include "game.h"

namespace fillergame {

Game::Game(const int window_width, const int window_height, const int margin, const Board &board, const Player &player1,
             const Player &player2) : window_width_(window_width), window_height_(window_height), margin_(margin),
             board_(board), player1_(player1), player2_(player2), tiles_left_(board.GetHeight() * board.GetWidth()) {}

void Game::Display() const {
  int n_tiles_width = board_.GetWidth();
  int n_tiles_height = board_.GetHeight();

  float tile_width = float(window_width_) / float(n_tiles_width);
  float tile_height = float(window_height_) / float(n_tiles_height);

  for (int i = 0; i < board_.GetWidth(); i++) {
    for (int j = 0; j < board_.GetHeight(); j++) {
      ci::gl::color(ci::Color(board_.GetTileColor(i, j)));

      glm::vec2 top_left = glm::vec2(i * tile_width, j * tile_height);
      glm::vec2 bottom_right = glm::vec2((i + 1) * tile_width, (j + 1) * tile_height);

      ci::Rectf tile(top_left, bottom_right);
      ci::gl::drawSolidRect(tile);
    }
  }
}

void Game::RunGame() {
  int turn = 1;

  while (!GameOver()) {
    char* color = "blue";

    /*
    if (turn == 1) {
      color = player1_.GetMove();
    }
    else {
      color = player2_.GetMove();
    }
     */

    tiles_left_ -= board_.UpdateBoard(turn, color);
    turn = (turn + 1) % 2 + 1;

    Display();
  }
}

bool Game::GameOver() {
  return tiles_left_ == 0;
}

void Game::UpdateBoard() {
  char* color = "blue";
  board_.UpdateBoard(1, color);
}

}
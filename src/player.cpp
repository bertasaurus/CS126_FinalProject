#pragma once

#include "player.h"

namespace fillergame {

char* Player::GetMove(const Board& board) const {
  return "blue";
}

bool Player::ShouldGetManualInput() const {
  return false;
}

}
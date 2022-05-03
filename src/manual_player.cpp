#pragma once

#include "manual_player.h"

namespace fillergame {

char* ManualPlayer::GetMove(const Board& board) const {
  return "black";
}

bool ManualPlayer::ShouldGetManualInput() const {
  return true;
}

}
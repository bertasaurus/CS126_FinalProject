#pragma once

#include "player.h"

namespace fillergame {

char* Player::GetMove() const {
  return "blue";
}

bool Player::IsManualPlayer() const {
  return true;
}

}
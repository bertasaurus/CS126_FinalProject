#pragma once

#include "player.h"

namespace fillergame {

class ManualPlayer : public Player {
  public:
    char* GetMove(const Board& board) const override;

    bool ShouldGetManualInput() const override;
};

}
#pragma once

#include "player.h"

namespace fillergame {

class ManualPlayer : Player {
  public:
    char* GetMove() const;
};

}
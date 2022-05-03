#pragma once

#include "board.h"
namespace fillergame {

class Player {
  public:
    virtual char* GetMove(const Board& board) const;

    virtual bool ShouldGetManualInput() const;
};

}
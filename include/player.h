#pragma once

namespace fillergame {

class Player {
  public:
    char* GetMove() const;

    bool IsManualPlayer() const;
};

}
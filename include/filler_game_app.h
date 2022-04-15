#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "board.h"
#include "player.h"
#include "game.h"

namespace fillergame {

class FillerGameApp : public ci::app::App {
  private:
    Game game_;

    const std::vector<char*> kColors_ {"black", "purple", "green", "yellow", "blue", "pink"};

    const int kTilesWidth_ = 12;
    const int kTilesHeight_ = 10;

    const int kWindowWidth_ = 800;
    const int kWindowHeight_ = 800;
    const int kMargin_ = 50;

  public:
    FillerGameApp();

    void draw() override;
    void update() override;

};

}
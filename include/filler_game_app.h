#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "board.h"
#include "player.h"
#include "manual_player.h"
#include "game.h"

namespace fillergame {

class FillerGameApp : public ci::app::App {
  private:
    Game game_;



  public:
    FillerGameApp();

    void draw() override;
    void update() override;

    const int kTilesWidth = 12;
    const int kTilesHeight = 10;

    const int kWindowWidth = 800;
    const int kWindowHeight = 800;
    const int kMargin = 50;

    const std::vector<char*> kColors {"blue", "green", "red", "purple", "yellow", "pink"};
};

}
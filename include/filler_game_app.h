#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "board.h"
#include "player.h"
#include "manual_player.h"

namespace fillergame {

class FillerGameApp : public ci::app::App {
  private:
    Board board_;
    Player player1_;
    Player player2_;

    int turn_ = 1;

    void DrawButtons() const;

    void DrawBoard() const;

  public:
    FillerGameApp();

    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void update() override;

    const int kTilesWidth = 12;
    const int kTilesHeight = 10;

    const int kWindowWidth = 800;
    const int kWindowHeight = 800;
    const int kMargin = 70;

    const int kBottomSpace = 150;
    const int kButtonSpacing = 50;

    const int kBoardWidth = kWindowWidth - 2 * kMargin;
    const int kBoardHeight = kWindowHeight - kBottomSpace - 3 * kMargin;

    const std::vector<char*> kColors {"blue", "green", "red", "purple", "yellow", "pink"};
};

}
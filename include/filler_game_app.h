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

    float timer_ = 0;

    int turn_ = 1;

    void DrawButtons() const;

    void DrawBoard() const;

    void DrawScoreBoard() const;

    void InputMove(const int player_idx, char* color);

    std::vector<glm::vec2> GetButtonLocations() const;

    float CalculateButtonSize() const;

  public:
    FillerGameApp();

    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void update() override;

    const int kTilesWidth = 14;
    const int kTilesHeight = 8;

    const int kTitleHeight = 80;

    const int kWindowWidth = 800;
    const int kWindowHeight = 800;
    const int kMargin = 50;

    const int kButtonSpacing = 60;

    const int kBoardWidth = kWindowWidth - 2 * kMargin;
    const int kBoardHeight = 400;

    const float kAnimationTime = 21;
    const float kAnimationScalar = 0.7;

    const std::vector<char*> kColors {"blue", "green", "red", "purple", "yellow", "pink"};
};

}
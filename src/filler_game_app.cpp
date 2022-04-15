#include "filler_game_app.h"

namespace fillergame {

FillerGameApp::FillerGameApp() : game_(kWindowWidth_, kWindowHeight_, kMargin_,
         Board(kTilesWidth_, kTilesHeight_, kColors_), Player(), Player()) {

}

void FillerGameApp::draw() {
  game_.Display();
}

void FillerGameApp::update() {
  game_.UpdateBoard();
}

}

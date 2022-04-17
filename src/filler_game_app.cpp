#include "filler_game_app.h"

namespace fillergame {

FillerGameApp::FillerGameApp() : game_(600, 600, 50,
                                         Board(12, 10, std::vector<char*> {"blue", "green", "red", "purple", "yellow", "pink"}),Player(), Player()) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);

}

void FillerGameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  ci::gl::translate(kMargin, kMargin);
  game_.Display();
  ci::gl::translate(-kMargin, -kMargin);
}

void FillerGameApp::update() {
  //game_.UpdateBoard();
}

}

#include "filler_game_app.h"

namespace fillergame {

FillerGameApp::FillerGameApp() : board_(12, 10, std::vector<char*> {"blue", "green", "red", "purple", "yellow", "pink"}),
  player1_(Player()), player2_(Player()) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);

}

void FillerGameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  ci::gl::translate(kMargin, kMargin);
  DrawBoard();
  ci::gl::translate(-kMargin, -kMargin);

  DrawButtons();

}

void FillerGameApp::DrawButtons() const {
  float button_bar_width = kWindowWidth - 2 * kButtonSpacing;
  int nColors = kColors.size();

  float square_size = (button_bar_width - (nColors - 1) * kButtonSpacing) / nColors;

  float xTranslate = kButtonSpacing;
  float yTranslate = kWindowHeight - square_size - kMargin;

  ci::gl::translate(xTranslate, yTranslate);

  for (int i = 0; i < nColors; i++) {
    glm::vec2 top_left = glm::vec2(kButtonSpacing * i + square_size * i, 0);
    glm::vec2 bottom_right = glm::vec2(kButtonSpacing * i + square_size * (i + 1), square_size);

    ci::gl::color(ci::Color(kColors[i]));
    ci::Rectf button(top_left, bottom_right);
    ci::gl::drawSolidRect(button);
  }

  ci::gl::translate(-xTranslate, -yTranslate);
}

void FillerGameApp::DrawBoard() const {
  int n_tiles_width = board_.GetWidth();
  int n_tiles_height = board_.GetHeight();

  float tile_width = float(kBoardWidth) / float(n_tiles_width);
  float tile_height = float(kBoardHeight) / float(n_tiles_height);

  for (int i = 0; i < board_.GetWidth(); i++) {
    for (int j = 0; j < board_.GetHeight(); j++) {
      ci::gl::color(ci::Color(board_.GetTileColor(i, j)));

      glm::vec2 top_left = glm::vec2(i * tile_width, j * tile_height);
      glm::vec2 bottom_right = glm::vec2((i + 1) * tile_width, (j + 1) * tile_height);

      ci::Rectf tile(top_left, bottom_right);
      ci::gl::drawSolidRect(tile);
    }
  }
}

void FillerGameApp::update() {

}

void FillerGameApp::mouseDown(ci::app::MouseEvent event) {

}

}

#include "filler_game_app.h"
#include <string>

namespace fillergame {

FillerGameApp::FillerGameApp() : board_(14, 8, std::vector<char*> {"blue", "green", "red", "purple", "yellow", "pink"}),
  player1_(ManualPlayer()), player2_(MonteCarloAgent(2, 5)) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);

}

void FillerGameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  DrawScoreBoard();

  DrawBoard();

  DrawButtons();
}

void FillerGameApp::DrawScoreBoard() const {
  ci::Font title_font("Times New Roman", 50);
  ci::Font score_font("Times New Roman", 50);

  std::string title = "Player 1 turn";

  if (turn_ == 2) {
    title = "Player 2 turn";
  }

  int game_winner = board_.GetGameWinner();
  if (game_winner == 1) {
    title = "Player 1 wins!";
  }
  if (game_winner == 2) {
    title = "Player 2 wins!";
  }
  if (game_winner == 3) {
    title = "It's a tie!";
  }

  ci::gl::drawString(std::to_string(board_.GetPlayerScore(1)), glm::vec2(kMargin, kMargin + kTitleHeight / 2), "white", score_font);

  ci::gl::drawStringCentered(title, glm::vec2(kWindowWidth / 2, kMargin + kTitleHeight / 2), "white", title_font);

  ci::gl::drawStringRight(std::to_string(board_.GetPlayerScore(2)), glm::vec2(kWindowWidth - kMargin, kMargin + kTitleHeight / 2), "white", score_font);
}

float FillerGameApp::CalculateButtonSize() const {
  int nColors = kColors.size();
  float button_bar_width = kWindowWidth - 2 * kButtonSpacing;
  float square_size = (button_bar_width - (nColors - 1) * kButtonSpacing) / nColors;

  return square_size;
}

std::vector<glm::vec2> FillerGameApp::GetButtonLocations() const {
  std::vector<glm::vec2> button_locations;

  int nColors = kColors.size();
  float square_size = CalculateButtonSize();

  float xTranslate = kButtonSpacing;
  float yTranslate = kTitleHeight + kBoardHeight + kMargin * 2 + (kWindowHeight - kTitleHeight - kBoardHeight - kMargin * 2 - square_size) / 2;
  glm::vec2 translate(xTranslate, yTranslate);

  for (int i = nColors - 1; i >= 0; i--) {
    glm::vec2 loc = glm::vec2(kButtonSpacing * i + square_size * i, 0) + translate;
    button_locations.push_back(loc);
  }

  return button_locations;
}

void FillerGameApp::DrawButtons() const {
  int nColors = kColors.size();
  float square_size = CalculateButtonSize();

  std::vector<glm::vec2> button_locations = GetButtonLocations();

  for (int i = 0; i < nColors; i++) {
    glm::vec2 top_left = button_locations.at(i);
    glm::vec2 bottom_right = glm::vec2(top_left.x + square_size, top_left.y + square_size);

    ci::gl::color(ci::Color(kColors[i]));
    ci::Rectf button(top_left, bottom_right);
    ci::gl::drawSolidRect(button);
  }
}

void FillerGameApp::DrawBoard() const {
  ci::gl::translate(kMargin, kMargin * 2 + kTitleHeight);
  int n_tiles_width = board_.GetWidth();
  int n_tiles_height = board_.GetHeight();

  float tile_width = float(kBoardWidth) / float(n_tiles_width);
  float tile_height = float(kBoardHeight) / float(n_tiles_height);

  // represents the player who most recently made a move
  int other_idx = turn_ % 2 + 1;

  for (int i = 0; i < board_.GetWidth(); i++) {
    for (int j = 0; j < board_.GetHeight(); j++) {
      ci::gl::color(ci::Color(board_.GetTileColor(i, j)));

      glm::vec2 top_left = glm::vec2(i * tile_width, j * tile_height);
      glm::vec2 bottom_right = glm::vec2((i + 1) * tile_width, (j + 1) * tile_height);

      if (other_idx == board_.GetTileOwner(i, j)) {
        float scalar = (timer_ / kAnimationTime) * kAnimationScalar;

        glm::vec2 translate = glm::vec2(tile_width * scalar / 2, tile_height * scalar / 2);

        top_left = top_left - translate;
        bottom_right = bottom_right + translate;
      }
      ci::Rectf tile(top_left, bottom_right);
      ci::gl::drawSolidRect(tile);
    }
  }
  ci::gl::translate(-kMargin, -(kMargin * 2 + kTitleHeight));

}

void FillerGameApp::update() {
  if (timer_ > 0) {
    timer_ = timer_ - 1;
    return;
  }

  if (turn_ == 1 && !player1_.ShouldGetManualInput()) {
    char* color = player1_.GetMove(board_);
    InputMove(turn_, color);
  }

  if (turn_ == 2 && !player2_.ShouldGetManualInput()) {
    char* color = player2_.GetMove(board_);
    InputMove(turn_, color);
  }

}

void FillerGameApp::mouseDown(ci::app::MouseEvent event) {
  // If the game is still doing an animation, do not process moust event
  if (timer_ > 0) {
    return;
  }

  // If the current player is not a manual player, do not process mouse event
  if ((turn_ == 1 && !player1_.ShouldGetManualInput()) || (turn_ == 2 && !player2_.ShouldGetManualInput())) {
    return;
  }

  std::vector<glm::vec2> button_locations = GetButtonLocations();
  float square_size = CalculateButtonSize();

  glm::vec2 pos = event.getPos();

  for (size_t i = 0; i < kColors.size(); i++) {
    glm::vec2 button = button_locations.at(i);
    if (pos.x > button.x && pos.x < button.x + square_size && pos.y > button.y && pos.y < button.y + square_size) {
      InputMove(turn_, kColors.at(i));
      return;
    }
  }
}

void FillerGameApp::InputMove(const int player_idx, char* color) {
  timer_ = kAnimationTime;
  board_.UpdateBoard(player_idx, color);
  turn_ = turn_ % 2 + 1;
}

}

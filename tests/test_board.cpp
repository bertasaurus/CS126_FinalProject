#include <catch2/catch.hpp>

#include <board.h>

using fillergame::Board;

TEST_CASE("Test board") {
  std::vector<char*> colors {"red", "blue", "green"};
  Board board(3, 3, colors);
  board.SetTileColor(0, 0, colors[0]);
  board.SetTileColor(0, 1, colors[0]);
  board.SetTileColor(0, 2, colors[1]);
  board.SetTileColor(1, 0, colors[2]);
  board.SetTileColor(1, 1, colors[1]);
  board.SetTileColor(1, 2, colors[2]);
  board.SetTileColor(2, 0, colors[1]);
  board.SetTileColor(2, 1, colors[2]);
  board.SetTileColor(2, 2, colors[1]);

  /*
   * Board colors should now be:
   *
   * R R B
   * G B G
   * B G B
   *
   */

  SECTION("Check that the score of player 1 is 1") {
    REQUIRE(board.GetPlayerScore(1) == 1);
  }

  SECTION("Check that the score of player 2 is 1") {
    REQUIRE(board.GetPlayerScore(2) == 1);
  }

  board.UpdateBoard(1, colors[2]);

  SECTION("Check that player 1 has a score of 2 after capturing a green tile") {
    REQUIRE(board.GetPlayerScore(1) == 2);
  }

  board.UpdateBoard(2, colors[0]);

  SECTION("Check that player 2 has a score of 1 after picking red and capturing no tiles") {
    REQUIRE(board.GetPlayerScore(2) == 1);
  }

  board.UpdateBoard(1, colors[0]);

  SECTION("Check that player 1 has captured a blob of red tiles after picking red") {
    REQUIRE(board.GetPlayerScore(1) == 4);
  }

  SECTION("Check that the game does not report the game is over when it is not") {
    REQUIRE(board.GetGameWinner() == 0);
  }

  board.UpdateBoard(2, colors[2]);
  board.UpdateBoard(1, colors[1]);

  SECTION("Check that the board properly reports that the game is over and that player 1 has won") {
    REQUIRE(board.GetGameWinner() == 1);
  }
}
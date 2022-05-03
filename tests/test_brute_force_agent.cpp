#include <catch2/catch.hpp>

#include <board.h>
#include <brute_force_agent.h>

using fillergame::Board;
using fillergame::BruteForceAgent;

TEST_CASE("Test recursion depth of 1") {
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
   * B G B
   * G B G
   * B R R
   *
   */

  BruteForceAgent agent = BruteForceAgent(1, 1);

  char* move = agent.GetMove(board);
  REQUIRE(strcmp(move, "red") == 0);

}

TEST_CASE("Test recursion depth greater than 1") {
  std::vector<char*> colors {"red", "blue", "green", "yellow"};
  Board board(3, 3, colors);
  board.SetTileColor(0, 0, colors[3]);
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
   * B G B
   * G B G
   * B R Y
   *
   */

  BruteForceAgent agent = BruteForceAgent(1, 3);

  char* move = agent.GetMove(board);
  REQUIRE(strcmp(move, "green") == 0);
}
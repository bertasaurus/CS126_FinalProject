#include "game.h"
#include "board.h"
#include "player.h"

using fillergame::Board;
using fillergame::Game;
using fillergame::Player;

int main() {
  std::vector<char*> colors {"blue", "green", "red", "purple", "yellow", "pink"};

  Game game(800, 800, 50, Board(12, 10, colors), Player(), Player());

  
}
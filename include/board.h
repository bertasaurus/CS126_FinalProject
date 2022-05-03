#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <assert.h>

namespace fillergame {

template <typename T>
struct vec2 {
  vec2(int d1, int d2) : d1(d1), d2(d2), data(d1 * d2) {};

  T at(int i1, int i2) const {
    return data[getIndex(i1, i2)];
  };

  void set(int i1, int i2, T val) {
    data[getIndex(i1, i2)] = val;
  }

  int getIndex(int i1, int i2) const {
    assert(i1 >= 0 && i1 < d1);
    assert(i2 >= 0 && i2 < d2);

    return (i1 * d2 + i2);
  };

  bool equals(const vec2<T>& other) {
    if (d1 != other.d1 || d2 != other.d2) {
      return false;
    }

    for (int i1 = 0; i1 < d1; i1++) {
      for (int i2 = 0; i2 < d2; i2++) {
        if (at(i1, i2) != other.at(i1, i2)) {
          return false;
        }
      }
    }

    return true;
  }

  int d1;
  int d2;
  std::vector<T> data;
};

class Board {
  private:
    int tiles_left_;
    int width_;
    int height_;
    std::vector<char*> colors_;

    vec2<char*> board_;
    vec2<int> tile_owner_;

    /**
     * Randomly genereates a color for each tile in the board
     */
    void GenerateColors();

    /**
     * Attempts to claim the tile for a player
     * @param player_idx
     * @param color
     * @param a
     * @param b
     */
    void ClaimTile(const int player_idx, char*& color, const int a, const int b);

    /**
     * Inputs player represented by player_idx choosing a specific color for their turn
     * @param player_idx
     * @param color
     */
    void ApplyMove(const int player_idx, char*& color);

  public:
    Board(const int width, const int height, const std::vector<char*>& colors);

    Board(const Board& other);

    char* GetTileColor(const int a, const int b) const;

    void SetTileColor(const int a, const int b, char*& color);

    void UpdateBoard(const int player_idx, char*& color);

    int GetWidth() const;

    int GetHeight() const;

    std::vector<char*> GetColors() const;

    int GetTileOwner(const int a, const int b) const;

    /**
     * Gets the winner of the game
     * @return 0 if game is not over, 1 if player 1 won, 2 if player 2 won, 3 if game is tied
     */
    int GetGameWinner() const;

    /**
     * Gets the score of a player
     * @param player_idx
     * @return
     */
    int GetPlayerScore(int player_idx) const;
};

}
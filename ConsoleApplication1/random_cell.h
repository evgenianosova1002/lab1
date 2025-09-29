#ifndef RANDOM_CELL_H
#define RANDOM_CELL_H

#include <random>
#include <utility>

class RandomCell {
private:
    int board_size;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    explicit RandomCell(int board_size)
        : board_size(board_size),
          gen(std::random_device{}()),
          dist(0, board_size - 1) {}

    std::pair<int, int> operator()() { return {dist(gen), dist(gen)}; }
};

#endif

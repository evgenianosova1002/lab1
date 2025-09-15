#pragma once

#include <vector>
#include <random>

class Board {
private:
    int board_size;
    int sell_selection;
\
    std::vector<std::vector<int>> frequencies;

    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    Board(int board_size, int sell_selection);

    void runExperiment();

    double mean_multiplicity() const;

    double median_multiplicity() const;
};

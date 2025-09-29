#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "random_cell.h"

class Board {
private:
    int board_size;
    int cell_selection_count;

    std::vector<std::vector<int>> cell_frequencies;
    RandomCell random_cell_picker;

public:
    Board(int board_size, int cell_selection_count);

    void run_experiment();
    void reset();

    double mean_multiplicity() const;
    double median_multiplicity() const;

    const std::vector<std::vector<int>>& frequencies() const { return cell_frequencies; }
};

#endif

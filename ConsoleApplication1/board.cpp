#include "board.h"

#include <algorithm>
#include <numeric>

using namespace std;

Board::Board(int board_size, int cell_selection_count)
    : board_size(board_size),
      cell_selection_count(cell_selection_count),
      cell_frequencies(board_size, vector<int>(board_size, 0)),
      random_cell_picker(board_size) {}

void Board::reset() {
    for (auto& row : cell_frequencies) {
        fill(row.begin(), row.end(), 0);
    }
}

void Board::run_experiment() {
    reset();
    for (int i = 0; i < cell_selection_count; ++i) {
        const auto [row, col] = random_cell_picker();
        ++cell_frequencies[row][col];
    }
}

double Board::mean_multiplicity() const {
    double total_selections = 0.0;
    for (const auto& row : cell_frequencies) {
        total_selections += accumulate(row.cbegin(), row.cend(), 0.0);
    }
    const double cells = 1.0 * board_size * board_size;
    return total_selections / cells;
}

double Board::median_multiplicity() const {
    vector<int> flat;
    flat.reserve(board_size * board_size);

    for (const auto& row : cell_frequencies) {
        copy(row.cbegin(), row.cend(), back_inserter(flat));
    }

    sort(flat.begin(), flat.end());

    const auto n = flat.size();
    if (n % 2 == 1) {
        return flat[n / 2];
    }
    return 0.5 * (flat[n / 2 - 1] + flat[n / 2]);
}
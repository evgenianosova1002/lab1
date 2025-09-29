#include "board.h"

#include <algorithm>

using namespace std;

// TODO(@evgenianosova1002): use namespace std consistently
Board::Board(int board_size, int cell_selection_count)
    : board_size(board_size),
      cell_selection_count(cell_selection_count),
      cell_frequencies(board_size, vector<int>(board_size, 0)),
      random_cell_picker(board_size) {}

void Board::reset() {
  for (auto& row : cell_frequencies) {
    // TODO(@evgenianosova1002): use stl
    fill(row.begin(), row.end(), 0);
  }
}

void Board::run_experiment() {
  reset();
  for (int i = 0; i < cell_selection_count; ++i) {
    // TODO(@evgenianosova1002): use structured bindings
    const auto [row, col] = random_cell_picker();
    // TODO(@evgenianosova1002): use pre- or post-increment consistently
    ++cell_frequencies[row][col];
  }
}

double Board::mean_multiplicity() const {
  // TODO(@evgenianosova1002): use the right type from the get go
  auto total_selections = 0.0;
  for (const auto& row : cell_frequencies) {
    total_selections += accumulate(row.cbegin(), row.cend(), 0.0);
  }
  const auto cells = board_size * 1. * board_size;
  return total_selections / cells;
}

double Board::median_multiplicity() const {
  vector<int> flat;
  flat.reserve(board_size * board_size);

  // TODO(@evgenianosova1002): use consistent bracing style
  // TODO(@annuzzya): consider making flatten a separate function
  for (const auto& row : cell_frequencies) {
    copy(row.cbegin(), row.cend(), back_inserter(flat));
  }

  // TODO(@evgenianosova1002): use standard sort or nth_element
  sort(flat.begin(), flat.end());

  const auto n = flat.size();
  if (n % 2 == 1) {
    return flat[n / 2];
  }
  return 0.5 * (flat[n / 2 - 1] + flat[n / 2]);
}

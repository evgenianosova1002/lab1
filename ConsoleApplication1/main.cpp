#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "board.h"

using namespace std;

static void print_heatmap(const vector<vector<int>>& grid) {
  auto max_val = grid[0][0];
  // TODO(@annuzzya): one thing at a time, max width = width of max value
  // or max_element(flattened.cbegin(), flattened.cend())
  // requires a flatten function!
  for (const auto& row : grid) {
    max_val = max(max_val, *max_element(row.cbegin(), row.cend()));
  }
  const auto width = to_string(max_val).size();
  for (const auto& row : grid) {
    // TODO(@annuzzya): use consistent bracing style
    for (auto v : row) {
      cout << setw(width + 1) << v;
    }
    cout << '\n';
  }
}

int main() {
  // TODO(@annuzzya): you only input 2 integers, no need for sync off

  int board_size = 0;
  int cell_selection_count = 0;

  // TODO(@annuzzya): your memory usage is quadratic in n, so this can cause an
  // out_of_memory exception that you will not catch
  cout << "Enter n (board size, n > 0): ";
  if (!(cin >> board_size) || board_size <= 0) {
    // TODO(@annuzzya): this is not an appropriate exception handling
    cerr << "Error: n must be > 0.\n";
    return 1;
  }

  cout << "Enter t (number of cell selections, t >= 0): ";
  if (!(cin >> cell_selection_count) || cell_selection_count < 0) {
    cerr << "Error: t must be >= 0.\n";
    return 1;
  }

  Board board(board_size, cell_selection_count);
  board.run_experiment();

  double r = static_cast<double>(cell_selection_count) /
             (static_cast<double>(board_size) * board_size);

  // TODO(@annuzzya, @evgenianosova1002): use const auto whenever possible
  const auto mean_value = board.mean_multiplicity();
  const auto median_value = board.median_multiplicity();

  cout << fixed << setprecision(6);
  cout << "\nMain Results:\n";
  cout << "n = " << board_size << ", t = " << cell_selection_count
       << ", r = t/n^2 = " << r << "\n";

  cout << "\nMean multiplicity:   " << mean_value << "\n";
  cout << "Median multiplicity: " << median_value << "\n";

  cout << "\nFrequency heatmap (" << board_size << "x" << board_size << "):\n";
  print_heatmap(board.frequencies());

  cout << "\nExperiment with different r:\n";
  vector<double> r_values = {0.5, 1.0, 2.0, 5.0};

  for (const auto rv : r_values) {
    // TODO(@annuzzya): this expression can overflow with t becoming zero and
    // causing out_of_range exceptions in median call. This is why you don't
    // handle exceptions with cerr and return. Better to throw and catch more
    // than initially intended than to miss out on something
    const int t = rv * board_size * board_size;
    Board b(board_size, t);
    b.run_experiment();
    cout << "r = " << rv << " (t = " << t << "): "
         << "mean = " << b.mean_multiplicity()
         << ", median = " << b.median_multiplicity() << "\n";
  }

  return 0;
}

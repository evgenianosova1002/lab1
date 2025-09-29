#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "board.h"

using namespace std;

static void print_heatmap(const vector<vector<int>>& grid) {
    auto max_val = grid[0][0];
    for (const auto& row : grid) {
        max_val = max(max_val, *max_element(row.cbegin(), row.cend()));
    }

    const auto width = to_string(max_val).size();
    for (const auto& row : grid) {
        for (auto v : row) {
            cout << setw(static_cast<int>(width) + 1) << v;
        }
        cout << '\n';
    }
}

int main() {
    int board_size = 0;
    int cell_selection_count = 0;

    cout << "Enter n (board size, n > 0): ";
    if (!(cin >> board_size) || board_size <= 0) {
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

    const double r = static_cast<double>(cell_selection_count) /
                     (static_cast<double>(board_size) * board_size);

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
        const int t = static_cast<int>(rv * board_size * board_size);
        Board b(board_size, t);
        b.run_experiment();
        cout << "r = " << rv
             << " (t = " << t << "): "
             << "mean = " << b.mean_multiplicity()
             << ", median = " << b.median_multiplicity() << "\n";
    }

    return 0;
}
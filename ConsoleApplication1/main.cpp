#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

static void print_heatmap(const vector<vector<int>>& grid) {

	int width = 0;
	for (const auto& row : grid)

		for (int v : row) {

			int w = static_cast<int>(to_string(v).size());
			if (w > width) width = w;
		}
	for (const auto& row : grid) {

		for (int v : row) cout << setw(width + 1) << v;
		cout << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

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

	double r = static_cast<double>(cell_selection_count) /
			   (static_cast<double>(board_size) * board_size);

	double mean_value = board.mean_multiplicity();
	double median_value = board.median_multiplicity();

	cout << fixed << setprecision(6);
	cout << "\nMain Results:\n";
	cout << "n = " << board_size
			  << ", t = " << cell_selection_count
			  << ", r = t/n^2 = " << r << "\n";

	cout << "Mean multiplicity:   " << mean_value << "\n";
	cout << "Median multiplicity: " << median_value << "\n";

	cout << "\nFrequency heatmap (" << board_size << "x" << board_size << "):\n";
	print_heatmap(board.frequencies());

	return 0;
}

#include "board.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

void print_heatmap(const vector<vector<int>>& grid) {
	for (const auto& row : grid) {
		for (int v : row) {
			cout << v << " ";
		}
		cout << "\n";
	}
}

int main()
{
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

	cout << "n = " << board_size
			  << ", t = " << cell_selection_count
			  << ", r = t/n^2 = " << r << "\n";
	cout << "Mean multiplicity:   " << mean_value << "\n";
	cout << "Median multiplicity: " << median_value << "\n";


	return 0;
}

#include "board.h"

using namespace std;

Board::Board(int board_size, int cell_selection_count)

	: board_size(board_size),
	cell_selection_count(cell_selection_count),
	cell_frequencies(board_size, std::vector<int>(board_size, 0)),
	random_cell_picker(board_size) {}

void Board::reset() {

	for (auto& row : cell_frequencies) {

		for (auto& val : row) {
			val = 0;
		}
	}
}

void Board::run_experiment() {

	reset();
	for (int i = 0; i < cell_selection_count; ++i) {

		pair<int,int> cell = random_cell_picker();
		int row = cell.first;
		int col = cell.second;
		cell_frequencies[row][col]++;
	}
}

double Board::mean_multiplicity() const {

	long long total_selections = 0;

	for (const auto& row : cell_frequencies) {

		for (int val : row) {

			total_selections += val;
		}
	}
	long long cells = 1LL * board_size * board_size;
	return static_cast<double>(total_selections) / static_cast<double>(cells);
}
static void insertion_sort(std::vector<int>& data) {

	for (size_t i = 1; i < data.size(); ++i) {

		int key = data[i];
		int j = static_cast<int>(i) - 1;

		while (j >= 0 && data[j] > key) {

			data[j + 1] = data[j];
			--j;
		}
		data[j + 1] = key;
	}
}

double Board::median_multiplicity() const {

	std::vector<int> flat;
	flat.reserve(static_cast<size_t>(board_size) * static_cast<size_t>(board_size));

	for (const auto& row : cell_frequencies) {

		for (int val : row) flat.push_back(val);
	}

	insertion_sort(flat);

	size_t n = flat.size();
	if (n % 2 == 1) return static_cast<double>(flat[n / 2]);
	return 0.5 * (flat[n / 2 - 1] + flat[n / 2]);
}

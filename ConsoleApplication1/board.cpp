#include "board.h"

using namespace std;

Board(int board_size, int sell_selection)

	: board_size(board_size),
	cell_selection_count(cell_selection_count),
	frequencies(board_size, 
	std::vector<int>(board_size, 0)),
	random_cell_picker(board_size) {}

void Board::run_experiment() {

	for (int i = 0; i < cell_selection_count; ++i) {

		pair<int,int> cell = random_cell_picker();
		int row = cell.first;
		int col = cell.second;
		frequencies[row][col]++;
	}
}


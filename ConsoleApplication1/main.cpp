#include "board.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int board_size = 0;
	int cell_selection_count = 0;

	cout << "Enter n (board size): ";
	cin >> board_size;

	cout << "Enter t (number of cell selections): ";
	cin >> cell_selection_count;

	if (board_size <= 0) {
		cerr << "Error: n must be > 0.\n";
		return 1;
	}
	if (cell_selection_count < 0) {
		cerr << "Error: t must be >= 0.\n";
		return 1;
	}

	return 0;
}

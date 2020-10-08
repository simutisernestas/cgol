#include <algorithm>
#include "cgol_logic.hpp"

// TODO optimize
void CGOLLogic::runGeneration(bool *board, const int &size)
{
	bool *future = new bool[size * size];
	for (int i = 0; i < size * size; ++i)
		future[i] = false;

	for (int l = 0; l < size; l++) {
		for (int m = 0; m < size; m++) {
			int alive_count = 0;
			for (int y = std::max(l - 1, 0); y < std::min(l + 2, size); ++y)
				for (int x = std::max(m - 1, 0); x < std::min(m + 2, size); ++x)
					alive_count += board[y * size + x];
			alive_count -= board[l * size + m];

			if (board[l * size + m] && (alive_count < 2)) {
				// underpopulation
				future[l * size + m] = false;
			}
			else if (board[l * size + m] && (alive_count > 3)) {
				// over population
				future[l * size + m] = false;
			}
			else if (!board[l * size + m] && (alive_count == 3)) {
				// reproduction
				future[l * size + m] = true;
			}
			else if (board[l * size + m] && (alive_count == 3 || alive_count == 2)) {
				// lives on
				future[l * size + m] = board[l * size + m];
			}
		}
	}

	for (int i = 0; i < size * size; ++i)
		board[i] = future[i];

	delete[] future;
}

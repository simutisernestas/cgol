#include <algorithm>
#include "cgol_logic.hpp"
#include <cstddef>

void CGOLLogic::runGeneration(std::vector<byte> &board, const int &width)
{
	std::vector<byte> tmp_board;
	tmp_board.resize(board.size());

	for (int row = 0; row < width; row++) {
		for (int col = 0; col < width; col++) {
			int alive_count = 0;

			for (int y = std::max(row - 1, 0); y < std::min(row + 2, width); ++y)
				for (int x = std::max(col - 1, 0); x < std::min(col + 2, width); ++x)
					alive_count += std::to_integer<int>(board[y * width + x]);

			alive_count -= std::to_integer<int>(board[row * width + col]);

			if (isCellAlive(board[row * width + col]) && (alive_count < 2)) {
				// underpopulation
				tmp_board[row * width + col] = byte{0};
			}
			else if (isCellAlive(board[row * width + col]) && (alive_count > 3)) {
				// over population
				tmp_board[row * width + col] = byte{0};
			}
			else if (!isCellAlive(board[row * width + col]) && (alive_count == 3)) {
				// reproduction
				tmp_board[row * width + col] = byte{1};
			}
			else if (isCellAlive(board[row * width + col]) && (alive_count == 3 || alive_count == 2)) {
				// lives on
				tmp_board[row * width + col] = board[row * width + col];
			}
		}
	}

	board = tmp_board;
}

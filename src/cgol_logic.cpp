#include <algorithm>
#include "include/cgol_logic.hpp"
#include <cstddef>

void CGOLLogic::runGeneration(std::shared_ptr<CGOLBoard> board)
{
	auto tmp_board = std::make_unique<CGOLBoard>(*board);
	int width = board->getSize();

	for (int row = 0; row < width; row++) {
		for (int col = 0; col < width; col++) {
			int alive_count = 0;

			for (int y = std::max(row - 1, 0); y < std::min(row + 2, width); ++y)
				for (int x = std::max(col - 1, 0); x < std::min(col + 2, width); ++x)
					alive_count += std::to_integer<int>(board->getAt(y, x));

			alive_count -= std::to_integer<int>(board->getAt(row, col));

			if (isCellAlive(board, row, col) && (alive_count < 2)) {
				// underpopulation
				tmp_board->setAt(byte{0}, row, col);
			}
			else if (isCellAlive(board, row, col) && (alive_count == 3 || alive_count == 2)) {
				// lives on
				tmp_board->setAt(byte{1}, row, col);
			}
			else if (isCellAlive(board, row, col) && (alive_count > 3)) {
				// over population
				tmp_board->setAt(byte{0}, row, col);
			}
			else if (!isCellAlive(board, row, col) && (alive_count == 3)) {
				// reproduction
				tmp_board->setAt(byte{1}, row, col);
			}
		}
	}

	*board = *tmp_board;
}

bool CGOLLogic::isCellAlive(std::shared_ptr<CGOLBoard> board, const int &row, const int &col)
{
	return board->getAt(row, col) == byte{1};
}
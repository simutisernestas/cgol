#ifndef CGOL_LOGIC_HPP
#define CGOL_LOGIC_HPP

#include <memory>

#include "cgol_board.hpp"

using std::byte;

class CGOLLogic
{

public:
	static constexpr byte CELL_ALIVE = byte{1};
	static constexpr byte CELL_DEAD = byte{0};

	static void runGeneration(std::shared_ptr<CGOLBoard> board);

	static bool isCellAlive(const std::shared_ptr<CGOLBoard> &board, const int &row, const int &col);

	// prevent object creation - only static methods available
	CGOLLogic() = delete;
	CGOLLogic(CGOLLogic const &) = delete;
	void operator=(CGOLLogic const &) = delete;

};

#endif //CGOL_LOGIC_HPP

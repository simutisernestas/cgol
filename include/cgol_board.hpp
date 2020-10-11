#ifndef CGOL_BOARD_HPP
#define CGOL_BOARD_HPP

#include <cstddef>
#include <random>

using std::byte;

class CGOLBoard
{

public:
	enum State
	{
		Random, Empty, Checkered
	};

	CGOLBoard();
	explicit CGOLBoard(const int& size, const State& init_state = Empty);

	[[nodiscard]] int getSize() const;

	[[nodiscard]] const byte &getAt(const int &row, const int &col) const;
	void setAt(const byte &value, const int &row, const int &col);

	void initState(const CGOLBoard::State &s);
	void initBoard(const int &size, const CGOLBoard::State &s);

private:
	int size_; // equal sides
	std::vector<byte> board_;
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> random_dist_;

	void initEmpty();
	void initRandom();
	void initCheckered();
};


#endif //CGOL_BOARD_HPP

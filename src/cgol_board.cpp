#include <algorithm>
#include <QtCore/QMetaType>

#include "include/cgol_board.hpp"

CGOLBoard::CGOLBoard()
	: size_{},
	  rng_{std::random_device()()},
	  random_dist_{1, 10}
{
}

CGOLBoard::CGOLBoard(const int &size, const CGOLBoard::State &init_state)
	: size_{size},
	  rng_{std::random_device()()},
	  random_dist_{1, 10}
{
	initBoard(size, init_state);
}

void CGOLBoard::initBoard(const int &size, const CGOLBoard::State &s)
{
	size_ = size;
	board_.resize(size_ * size_);
	initState(s);
}

void CGOLBoard::initState(const CGOLBoard::State &s)
{
	switch (s) {
		case CGOLBoard::State::Random: initRandom();
			break;
		case CGOLBoard::State::Empty: initEmpty();
			break;
		case CGOLBoard::State::Checkered: initCheckered();
			break;
	}
}

void CGOLBoard::initEmpty()
{
	for (byte &i : board_)
		i = byte{0};
}

void CGOLBoard::initRandom()
{
	for (byte &i : board_) {
		auto rand_num = random_dist_(rng_);
		i = byte{rand_num <= 5};
	}
}

void CGOLBoard::initCheckered()
{
	for (int row = 0; row < size_; ++row) {
		for (int col = 0; col < size_; ++col) {
			board_[row * size_ + col] = byte{!((row + col) & 1)};
		}
	}
}

void CGOLBoard::setAt(const byte &value, const int &row, const int &col)
{
	int index = row * size_ + col;

	if (index >= size_ * size_ || row < 0 || col < 0)
		throw std::out_of_range("Board index out of range, while setting tile value.");

	board_[index] = value;
}

int CGOLBoard::getSize() const
{
	return size_;
}

const byte &CGOLBoard::getAt(const int &row, const int &col) const
{
	int index = row * size_ + col;

	if (index >= size_ * size_ || row < 0 || col < 0)
		throw std::out_of_range("Board index out of range, while getting tile value.");

	return board_[index];
}

Q_DECLARE_METATYPE(CGOLBoard)
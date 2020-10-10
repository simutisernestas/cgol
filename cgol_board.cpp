#include <algorithm>

#include "cgol_board.hpp"

CGOLBoard::CGOLBoard()
	: size_{},
	  rng_{std::random_device()()},
	  random_dist_{1, 10}
{
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

void CGOLBoard::setSize(const int &size)
{
	size_ = size;
	board_.resize(size_ * size_);
	std::fill(board_.begin(), board_.end(), byte{0});
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
	board_[row * size_ + col] = value;
}

int CGOLBoard::getSize() const
{
	return size_;
}

const byte &CGOLBoard::getAt(const int &row, const int &col) const
{
	return board_[row * size_ + col];
}

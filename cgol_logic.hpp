#ifndef CGOL_LOGIC_HPP
#define CGOL_LOGIC_HPP

using std::byte;

class CGOLLogic
{

public:
	static void runGeneration(std::vector<byte> &board, const int &width);

	static inline bool isCellAlive(byte cell)
	{
		return cell == byte{1};
	}

// prevent object creation, since only static methods available
private:
	CGOLLogic() = default;
public:
	CGOLLogic(CGOLLogic const &) = delete;
	void operator=(CGOLLogic const &) = delete;

};

#endif //CGOL_LOGIC_HPP

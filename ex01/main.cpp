#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl, 1;
	RPN rpn;
	if (!rpn.checkInput(argv[1]))
		return 1;
	try {
		int result = rpn.calculate(argv[1]);
		std::cout << result << std::endl;
	} catch (std::exception& e) {
		return std::cerr << "Error: " << e.what() << std::endl, 1;
	}
	return 0;
}
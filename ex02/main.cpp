#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return std::cerr << "Usage: " << argv[0] << " <input>" << std::endl, 1;

	PmergeMe pmm;
	if (!pmm.parseInput(argv[1]))
		return 1;
	pmm.sort();
	return 0;
}
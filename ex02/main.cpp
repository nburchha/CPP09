#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe pmm;
	std::vector<std::string> inputs;
	for (int i = 1; i < argc; ++i)
		inputs.emplace_back(argv[i]);
	if (!pmm.parseInput(inputs))
		return 1;
	pmm.sort();
	return 0;
}
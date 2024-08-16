#include "PmergeMe.hpp"
#include "PmergeMe.tpp"

PmergeMe::PmergeMe() : _vector() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
		return *this;
	_vector = other._vector;
	return *this;
}

bool PmergeMe::parseInput(const std::vector<std::string> &inputs)
{
	std::string concatenatedInput;
	for (const auto& input : inputs)
		concatenatedInput += input + " ";
	std::istringstream iss(concatenatedInput);
	std::string token;
	std::unordered_set<int> seenNumbers;
	for (std::string::const_iterator it = concatenatedInput.begin(); it != concatenatedInput.end(); ++it)
		if (!std::isdigit(*it) && *it != ' ')
			return std::cerr << "Invalid character in input: " << *it << std::endl, false;
	while (iss >> token)
	{
		char* end;
		long num = std::strtol(token.c_str(), &end, 10);
		if (*end != '\0')
			return std::cerr << "Invalid token: " << token << std::endl, false;
		if (num > std::numeric_limits<int>::max() || num < 0)
			return std::cerr << "Invalid token: Out of range: " << token << std::endl, false;
		if (std::find(_vector.begin(), _vector.end(), static_cast<int>(num)) != _vector.end())
			return std::cerr << "Invalid token: Duplicate: " << token << std::endl, false;
		_vector.push_back(static_cast<int>(num));
		_dq.push_back(static_cast<int>(num));
	}
	return true;
}

void PmergeMe::sort()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size() && i < 10; ++i) {
		std::cout << _vector[i] << " ";
	}
	std::cout << "[...]" << std::endl;
	double dqDuration = 0;
	double vectorDuration = 0;
	try {
		std::cout << "Sorting deque: ";
		dqDuration = mergeInsertionSort(_dq);
		std::cout << "Sorting vector: ";
		vectorDuration = mergeInsertionSort(_vector);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "After: ";
	for (size_t i = 0; i < _vector.size() && i < 10; ++i) {
		std::cout << _vector[i] << " ";
	}
	std::cout << "[...]" << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << vectorDuration << " ms" << std::endl;
	std::cout << "Time to process a range of " << _dq.size() << " elements with std::deque: " << dqDuration << " ms" << std::endl;
}
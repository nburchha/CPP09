#pragma once

#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

class PmergeMe
{
public:
	PmergeMe();
	~PmergeMe();
	bool parseInput(const std::vector<std::string> &inputs);
	void sort();
private:
	std::vector<int> _vector;
	std::deque<int> _dq;
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
};


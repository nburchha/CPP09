#pragma once

#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

class PmergeMe
{
public:
	PmergeMe();
	~PmergeMe();
	bool parseInput(const std::string &input);
	void sort();
private:
	std::vector<int> _vector;
	std::deque<int> _dq;
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

	// template <typename C>
	// C createSortedS(const std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs, typename C::value_type straggler);
	// template <typename C>
	// void mergeInsertionSort(C& arr);
	// template <typename C>
	// void handleStragger(C& arr, typename C::value_type& straggler);
	// template <typename C>
	// std::vector<std::pair<typename C::value_type, typename C::value_type> > createPairs(const C& arr);
	// template <typename C>
	// void sortEachPair(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs);
	// template <typename C>
	// void sortByLargerValue(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs);
	// std::vector<int> buildJacobInsertionSequence(int size);
	// template <typename C>
	// void insertPendElements(C& S, const std::vector<typename C::value_type>& pend, const std::vector<int>& insertionSequence);
	// template <typename C>
	// void handleStraggler(C& arr, typename C::value_type& straggler);
};


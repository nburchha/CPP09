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

bool PmergeMe::parseInput(const std::string &input)
{
	std::istringstream iss(input);
	std::string token;
	std::unordered_set<int> seenNumbers;

	for (std::string::const_iterator it = input.begin(); it != input.end(); ++it)
	{
		char c = *it;
		if (!std::isdigit(c) && c != ' ')
			return std::cerr << "Invalid character in input: " << c << std::endl, false;
	}
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
	std::cout << "Unsorted vector: ";
	for (size_t i = 0; i < _vector.size(); ++i) {
		std::cout << _vector[i] << " ";
	}
	std::cout << std::endl;

	mergeInsertionSort(_vector);
	mergeInsertionSort(_dq);


	std::cout << "Sorted vector: ";
	for (size_t i = 0; i < _vector.size(); ++i) {
		std::cout << _vector[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Sorted deque: ";
	for (size_t i = 0; i < _dq.size(); ++i) {
		std::cout << _dq[i] << " ";
	}
	std::cout << std::endl;
}

// template <typename C>
// static void handleStraggler(C& arr, typename C::value_type& straggler)
// {
// 	straggler = arr.back();
// 	arr.pop_back();
// }

// template<typename C>
// void PmergeMe::mergeInsertionSort(C& arr)
// {
// 	typename C::value_type straggler;
// 	bool hasStraggler = arr.size() % 2 != 0;

// 	if (hasStraggler)
// 		handleStraggler(arr, straggler);
// 	std::vector<std::pair<typename C::value_type, typename C::value_type> > pairs = createPairs(arr);
// 	sortEachPair(pairs);
// 	sortByLargerValue(pairs);
// 	C sortedArr = createSortedS(pairs, hasStraggler ? straggler : typename C::value_type());
// 	arr = sortedArr;
// }

// template<typename C>
// std::vector<std::pair<typename C::value_type, typename C::value_type> > PmergeMe::createPairs(const C& arr)
// {
// 	std::vector<std::pair<typename C::value_type, typename C::value_type> > pairs;
// 	for (size_t i = 0; i < arr.size(); i += 2)
// 		pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
// 	return pairs;
// }

// template <typename C>
// void PmergeMe::sortEachPair(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs)
// {
// 	for (size_t i = 0; i < pairs.size(); ++i)
// 		if (pairs[i].first > pairs[i].second)
// 			std::swap(pairs[i].first, pairs[i].second);
// }

// template <typename C>
// void PmergeMe::sortByLargerValue(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs)
// {
// 	std::sort(pairs.begin(), pairs.end(), [](const std::pair<typename C::value_type, typename C::value_type>& a, const std::pair<typename C::value_type, typename C::value_type>& b) {
// 		return a.second < b.second;
// 	});
// }

// template<typename C>
// C PmergeMe::createSortedS(const std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs, typename C::value_type straggler)
// {
// 	C S;
// 	std::vector<typename C::value_type> pend;
// 	for (size_t i = 0; i < pairs.size(); ++i) {
// 		S.push_back(pairs[i].second);
// 		pend.push_back(pairs[i].first);
// 	}
// 	if (!pend.empty()) {
// 		S.insert(S.begin(), pend[0]);
// 		pend.erase(pend.begin());
// 	}
// 	std::vector<int> insertionSequence = buildJacobInsertionSequence(pend.size());
// 	insertPendElements(S, pend, insertionSequence);
// 	if (straggler != typename C::value_type()) {
// 		typename C::iterator it = std::lower_bound(S.begin(), S.end(), straggler);
// 		S.insert(it, straggler);
// 	}
// 	return S;
// }

// std::vector<int> PmergeMe::buildJacobInsertionSequence(int size)
// {
// 	std::vector<int> sequence;
// 	if (size == 0)
// 		return sequence;
// 	sequence.push_back(1);
// 	for (int i = 2; i < size; ++i)
// 	{
// 		int next = sequence.back() + 1;
// 		sequence.push_back(next);
// 	}
// 	return sequence;
// }

// template <typename C>
// void PmergeMe::insertPendElements(C& S, const std::vector<typename C::value_type>& pend, const std::vector<int>& insertionSequence)
// {
// 	for (size_t i = 0; i < pend.size(); ++i)
// 	{
// 		typename C::value_type value = pend[i];
// 		size_t index = insertionSequence[i];
// 		if (index >= S.size()) {
// 			typename C::iterator it = std::lower_bound(S.begin(), S.end(), value);
// 			S.insert(it, value);
// 		}
// 		else
// 			S.push_back(value);
// 	}
// }
#include <chrono>

template<typename C>
void handleStraggler(C& arr, typename C::value_type& straggler)
{
	straggler = arr.back();
	arr.pop_back();
}

template<typename C>
void sortPairs(C& arr)
{
	for (size_t i = 1; i < arr.size(); i += 2)
		if (arr[i] < arr[i - 1])
			std::swap(arr[i], arr[i - 1]);
}

template <typename C>
void insertRange(C& a, typename C::iterator it1, typename C::iterator it2, int size)
{
	auto it3 = it2 + size;
	std::vector<typename C::value_type> ins(it2, it3);
	a.insert(it1, ins.begin(), ins.end());
}

template <typename C>
int merge(C& pairs, unsigned int size)
{
	auto it1 = pairs.begin();
	auto it2 = it1 + size;
	if (*it1 < *it2)
		std::swap_ranges(it1, it2, it2);
	for (size_t i = 1; i < pairs.size() / (2 * size); ++i)
	{
		it1 += 2 * size;
		it2 += 2 * size;
		if (*it1 < *it2)
			std::swap_ranges(it1, it2, it2);
	}
	if (2 * size <= pairs.size())
		size = merge(pairs, 2 * size);
	return size;
}

std::vector<int> buildJacobsthalSequence(int size)
{
	std::vector<int> sequence;
	if (size == 0)
		return sequence;
	sequence.push_back(0);
	if (size == 1)
		return sequence;
	sequence.push_back(1);
	for (int i = 2; i < size; ++i)
	{
		int next = sequence[i - 1] + 2 * sequence[i - 2];
		sequence.push_back(next);
	}
	return sequence;
}



template <typename C>
void insertPendElements(C& S, const std::vector<typename C::value_type>& pend)
{
	for (size_t i = 0; i < pend.size(); ++i)
	{
		typename C::value_type value = pend[i];
		typename C::iterator it = std::lower_bound(S.begin(), S.end(), value);
		S.insert(it, value);
	}
}



template<typename C>
C createSortedS(const std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs, typename C::value_type straggler)
{
	C S;
	std::vector<typename C::value_type> pend;
	for (size_t i = 0; i < pairs.size(); ++i) {
		S.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}
	if (!pend.empty()) {
		S.insert(S.begin(), pend[0]);
		pend.erase(pend.begin());
	}
	std::vector<int> insertionSequence = buildJacobsthalSequence(pend.size());
	insertPendElements(S, pend);
	if (straggler != typename C::value_type()) {
		typename C::iterator it = std::lower_bound(S.begin(), S.end(), straggler);
		S.insert(it, straggler);
	}
	return S;
}

template <typename C>
typename C::iterator binSearch(C& S, int size, typename C::iterator it1, int target)
{
	auto left = S.begin();
	auto right = it1 - size;
	auto mid = left + (std::distance(left, right) / size) / 2 * size;
	while (left != right && left + size != right)
	{
		if (*mid == target)
			return mid;
		if (*mid < target)
			left = mid;
		else
			right = mid;
		mid = left + (std::distance(left, right) / size) / 2 * size;
	}
	if (*right < target)
		return right + size;
	if (*mid < target)
		return mid + size;
	return mid;
}

template <typename C>
void insertionSort(C& pairs, int size, C& S)
{
	S.clear();
	auto it1 = pairs.begin();
	auto it2 = it1 + size;
	while (distance(it1, pairs.end()) >= 2 * size)
	{
		insertRange(S, S.end(), it1, size);
		it1 += 2 * size;
	}
	insertRange(S, S.end(), it2, size);
	unsigned int sortSize = 2;
	int idk = 0;
	int tab = pairs.size() / (2 * size);
	std::vector<int> insertionSequence = buildJacobsthalSequence(tab);
	for (int i = 1; i < tab; ++i)
	{
		if (idk == 0 || insertionSequence[idk] > insertionSequence[idk - 1])
			sortSize *= 2;
		if (sortSize > S.size() / size)
			sortSize = S.size() / size;
		while (insertionSequence[idk] >= tab)
			++idk;
		it2 = pairs.begin() + size * 2 * (tab);
		it1 = binSearch(S, size, S.begin() + (sortSize - 1) * size, *it2);
		insertRange(S, it1, it2, size);
	}
	if (pairs.size() % 2)
	{
		it2 = pairs.begin() + size * 2 * (tab);
		it1 = binSearch(S, size, S.end(), *it2);
		insertRange(S, it1, it2, size);
	}
	size /= 2;
	it1 = pairs.end() - (pairs.size() - S.size());
	S.insert(S.end(), it1, pairs.end());
	pairs = S;
	if (size >= 1)
		insertionSort(pairs, size / 2, S);
}

template<typename C>
double mergeInsertionSort(C& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	// typename C::value_type straggler;
	// bool hasStraggler = arr.size() % 2 != 0;

	// if (hasStraggler)
	// 	handleStraggler(arr, straggler);
	// std::vector<std::pair<typename C::value_type, typename C::value_type> > pairs = createPairs(arr);
	// sortEachPair<C>(pairs);
	int size = merge<C>(arr, 1) / 2;
	C S;
	insertionSort<C>(arr, size, S);
	// C sortedArr = createSortedS<C>(pairs, hasStraggler ? straggler : typename C::value_type());
	// arr = sortedArr;
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	return duration.count();
}

// use std::swap_ranges function to swap the ranges
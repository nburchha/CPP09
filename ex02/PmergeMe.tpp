template<typename C>
void handleStraggler(C& arr, typename C::value_type& straggler)
{
	straggler = arr.back();
	arr.pop_back();
}

template<typename C>
std::vector<std::pair<typename C::value_type, typename C::value_type> > createPairs(const C& arr)
{
	std::vector<std::pair<typename C::value_type, typename C::value_type> > pairs;
	for (size_t i = 0; i < arr.size(); i += 2)
		pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	return pairs;
}

template <typename C>
void sortEachPair(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
}

template <typename C>
void sortByLargerValue(std::vector<std::pair<typename C::value_type, typename C::value_type> >& pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
		for (size_t j = i + 1; j < pairs.size(); ++j)
			if (pairs[i].second > pairs[j].second)
				std::swap(pairs[i], pairs[j]);
}

std::vector<int> buildJacobInsertionSequence(int size)
{
	std::vector<int> sequence;
	if (size == 0)
		return sequence;
	sequence.push_back(1);
	int j0 = 0;
	int j1 = 1;
	for (int i = 2; i <= size; ++i)
	{
		int next = j1 + 2 * j0;
		sequence.push_back(next);
		j0 = j1;
		j1 = next;
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
	std::vector<int> insertionSequence = buildJacobInsertionSequence(pend.size());
	insertPendElements(S, pend);
	if (straggler != typename C::value_type()) {
		typename C::iterator it = std::lower_bound(S.begin(), S.end(), straggler);
		S.insert(it, straggler);
	}
	return S;
}

template<typename C>
void mergeInsertionSort(C& arr)
{
	typename C::value_type straggler;
	bool hasStraggler = arr.size() % 2 != 0;

	if (hasStraggler)
		handleStraggler(arr, straggler);
	std::vector<std::pair<typename C::value_type, typename C::value_type> > pairs = createPairs(arr);
	sortEachPair<C>(pairs);
	sortByLargerValue<C>(pairs);
	C sortedArr = createSortedS<C>(pairs, hasStraggler ? straggler : typename C::value_type());
	arr = sortedArr;
}


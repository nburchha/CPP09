#include <chrono>

template <typename C>
void swapRange(C &arr, typename C::iterator b, typename C::iterator c, int size)
{
	std::vector<typename C::value_type> firstRange(b, b + size);
	std::move(c, c + size, b);
	std::move(firstRange.begin(), firstRange.end(), c);
	(void)arr;
}

template <typename C>
void insertRange(C& a, typename C::iterator it1, typename C::iterator it2, int size)
{
	auto it3 = std::next(it2, size);
	std::vector<typename C::value_type> ins(it2, it3);
	a.insert(it1, ins.begin(), ins.end());
}

template <typename C>
int merge(C& arr, unsigned int size)
{
	auto it1 = arr.begin();
	auto it2 = std::next(it1, size);
	if (*it1 < *it2)
		swapRange(arr, it1, it2, size);
	for (size_t i = 1; i < arr.size() / (2 * size); ++i)
	{
		it1 = std::next(it1, 2 * size);
		it2 = std::next(it2, 2 * size);
		if (*it1 < *it2)
			swapRange(arr, it1, it2, size);
	}
	if (4 * size <= arr.size())
		size = merge(arr, size * 2);
	return size;
}

std::vector<int> buildJacobsthalSequence(int k)
{
	std::vector<int> sequence;
	int prev = 2;
	int curr;
	int i = 1;
	int g = 2;
	int size = 2;

	sequence.push_back(2);
	sequence.push_back(1);
	while (++i < k) {
		size *=2;
		g = size - g;
		curr = prev + g;
		while (curr > prev)
			sequence.push_back(curr--);
		prev = prev + g;
	}
	return sequence;
}

template <typename C>
typename C::iterator binSearch(C& arr, int size, typename C::iterator it1, int target)
{
	auto left = arr.begin();
	auto right = std::prev(it1, size);
	auto mid = std::next(left, (std::distance(left, right) / size) / 2 * size);
	while (!(left == right || std::next(left, size) == right))
	{
		if (*mid > target)
		{
			right = mid;
			mid = std::next(left, (std::distance(left, right) / size) / 2 * size);
		}
		else if (*mid < target)
		{
			left = mid;
			mid = left + (std::distance(left, right) / size) / 2 * size;
			mid = std::next(left, (std::distance(left, right) / size) / 2 * size);
		}
		else
			return mid;
	}
	if (*right < target)
		return std::next(right, size);
	if (*mid < target)
		return std::next(mid, size);
	return mid;
}

template <typename C>
void insertionSort(C& arr, int size, C& S)
{
	S.clear();
	auto it1 = arr.begin();
	auto it2 = std::next(it1, size);
	while (distance(it1, arr.end()) >= 2 * size)
	{
		insertRange(S, S.end(), it1, size);
		it1 = std::next(it1, 2 * size);
	}
	insertRange(S, S.begin(), it2, size);
	unsigned int sortSize = 2;
	int idk = 0;
	int tab = arr.size() / (2 * size);
	std::vector<int> insertionSequence = buildJacobsthalSequence(13);
	for (int i = 1; i < tab; i++)
	{
		if (idk == 0 || insertionSequence[idk] > insertionSequence[idk - 1])
			sortSize *= 2;
		if (sortSize > S.size() / size)
			sortSize = S.size() / size;
		while (insertionSequence[idk] >= tab)
			++idk;
		it2 = std::next(arr.begin(), size + 2 * size * insertionSequence[idk++]);
		it1 = binSearch(S, size, S.begin() + (sortSize - 1) * size, *it2);
		insertRange(S, it1, it2, size);
	}
	if ((arr.size() / size) % 2)
	{
		it2 = std::next(arr.begin(), size * 2 * tab);
		it1 = binSearch(S, size, S.end(), *it2);
		insertRange(S, it1, it2, size);
	}
	it1 = std::prev(arr.end(), arr.size() - S.size());
	S.insert(S.end(), it1, arr.end());
	arr = S;
	if (size / 2 >= 1)
		insertionSort(arr, size / 2, S);
}

template<typename C>
double mergeInsertionSort(C& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	int size = merge<C>(arr, 1);
	C S;
	if (size >= 1)
		insertionSort<C>(arr, size, S);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	for (size_t i = 1; i < arr.size(); ++i)
		if (arr[i] < arr[i - 1])
			throw std::runtime_error("Not sorted!");
	std::cout << "Sorted!" << std::endl;
	return duration.count();
}

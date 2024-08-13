#include <chrono>

template <typename C>
void swapRange(C &arr, typename C::iterator b, typename C::iterator c, int size)
{
	auto d = c + size;
	std::vector<int> ins(c, d);
	arr.erase(c, d);
	arr.insert(b, ins.begin(), ins.end());
}

template <typename C>
void insertRange(C& a, typename C::iterator it1, typename C::iterator it2, int size)
{
	auto it3 = it2 + size;
	std::vector<typename C::value_type> ins(it2, it3);
	a.insert(it1, ins.begin(), ins.end());
}

template <typename C>
int merge(C& arr, unsigned int size)
{
	auto it1 = arr.begin();
	auto it2 = it1 + size;
	if (*it1 < *it2)
		swapRange(arr, it1, it2, size);
	for (size_t i = 1; i < arr.size() / (2 * size); ++i)
	{
		it1 += 2 * size;
		it2 += 2 * size;
		if (*it1 < *it2)
			swapRange(arr, it1, it2, size);
	}
	std::cout << "size in merge: " << size << ", ";
	for (auto iterator : arr)
		std::cout << iterator << " ";
	std::cout << std::endl;
	size *= 2;
	if (2 * size <= arr.size())
		size = merge(arr, size);
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
	std::cout << "Jacobsthal sequence: ";
	for (size_t i = 0; i < sequence.size(); i++)
	{
		std::cout << sequence[i] << " ";
		if (i > 10) break;
	}
	std::cout << std::endl;
	return sequence;
}

template <typename C>
typename C::iterator binSearch(C& arr, int size, typename C::iterator it1, int target)
{
	auto left = arr.begin();
	auto right = it1 - size;
	auto mid = left + (std::distance(left, right) / size) / 2 * size;
	while (!(left == right || left + size == right))
	{
		if (*mid > target)
		{
			right = mid;
			mid = left + (std::distance(left, right) / size) / 2 * size;
		}
		else if (*mid < target)
		{
			left = mid;
			mid = left + (std::distance(left, right) / size) / 2 * size;
		}
		else
			return mid;
	}
	if (*right < target)
		return right + size;
	if (*mid < target)
		return mid + size;
	return mid;
}

template <typename C>
void insertionSort(C& arr, int size, C& S)
{
	S.clear();
	auto it1 = arr.begin();
	auto it2 = it1 + size;
	std::cout << "start of insertion size: " << size << std::endl;
	std::cout << "distance(it1, arr.end())" << distance(it1, arr.end()) << std::endl;
	while (distance(it1, arr.end()) >= 2 * size)
	{
		insertRange(S, S.end(), it1, size);
		it1 += 2 * size;
	}
	insertRange(S, S.end(), it2, size);
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
		it2 = arr.begin() + size + 2 * size * insertionSequence[idk++];
		it1 = binSearch(S, size, S.begin() + (sortSize - 1) * size, *it2);
		insertRange(S, it1, it2, size);
	}
	if ((arr.size() / size) % 2)
	{
		it2 = arr.begin() + size * 2 * tab;
		it1 = binSearch(S, size, S.end(), *it2);
		insertRange(S, it1, it2, size);
	}
	it1 = arr.end() - (arr.size() - S.size());
	S.insert(S.end(), it1, arr.end());
	arr = S;
	
	if (size / 2 >= 1)
	{
		std::cout << "end of insertion size: " << size << std::endl;
		insertionSort(arr, size / 2, S);
	}
}

template<typename C>
double mergeInsertionSort(C& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	int size = merge<C>(arr, 1);
	std::cout << "size: " << size << std::endl;
	C S;
	if (size >= 1)
		insertionSort<C>(arr, size, S);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	return duration.count();
}
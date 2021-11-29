#include <cstddef>
#include <functional>

/*****************************************************************************
 * Bubble sort:
 * Repeatedly step through the list, compare adjacent elements and swaps them 
 * if they are in the wrong order.
 * Complexity: ~N^2 compares and ~(N^2)/2 exchanges in the worst-case.
 *****************************************************************************/

template < typename T, template<typename> typename Container, 
           typename Compare = std::less<T> >
void BubbleSort0(Container<T>& a, Compare comp = Compare())
{
	using std::swap;
	for ( bool swapped = true; swapped; )
	{
		swapped = false;
		for ( size_t i = 1; i < a.size(); ++i )
			if ( comp(a[i], a[i-1]) )
			{
				swap(a[i-1], a[i]);
				swapped = true;
			}
	}
}

template <typename Container>
void BubbleSort1(Container& a)
{
	using std::swap;
	for ( bool swapped = true; swapped; )
	{
		swapped = false;
		for ( size_t i = 1; i < a.size(); ++i )
			if ( a[i] < a[i-1] )
			{
				swap(a[i-1], a[i]);
				swapped = true;
			}
	}
}

template <typename Container>
void BubbleSort2(Container& a)
{
	using std::swap;
	for ( size_t n = a.size(), new_n; n > 1; n = new_n )
	{
		new_n = 0;
		for ( size_t i = 1; i < n; ++i )
			if ( a[i] < a[i-1] )
			{
				swap(a[i-1], a[i]);
				new_n = i;
			}
	}  // All elements after the last swap are sorted, and don't need to be checked again
}



/*****************************************************************************
 * Selection sort:
 * In iteration i, find index min_i of smallest remaining entry,
 * swap a[i] and a[min_i].
 * Not stable sort.
 * Complexity: ~(N^2)/2 compares and N exchanges.
 *****************************************************************************/

template <typename Container>
void SelectionSort(Container& a)
{
	using std::swap;
	for ( size_t i = 0; i < a.size(); ++i )
	{
		size_t min_i = i;
		for ( size_t j = i + 1; j < a.size(); ++j )
			if ( a[j] < a[min_i] )  min_i = j;
		swap(a[i], a[min_i]);
	}
}



/*****************************************************************************
 * Insertion sort:
 * In iteration i, swap a[i] with each larger entry to its left.
 * Stable sort.
 * Complexity: ~(N^2)/4 compares and ~(N^2)/4 exchanges on average.
 *****************************************************************************/

template <typename Container>
void InsertionSort1(Container& a)
{
	using std::swap;
	for ( size_t i = 0; i < a.size(); ++i )
		for ( size_t j = i; j > 0 && a[j] < a[j-1]; --j )
			swap(a[j-1], a[j]);
}

template <typename Container>
void InsertionSort2(Container& a)
{
	for ( size_t i = 1; i < a.size(); ++i )
		if ( a[i] < a[i-1] )
		{
			auto tmp = a[i];
			size_t j = i;
			for ( ; j != 0 && tmp < a[j-1]; --j )  a[j] = a[j-1];
			a[j] = tmp;
		}
}

template <typename Container>
void InsertionSort3(Container& a)
{
	using std::swap;
	for ( size_t j = a.size() - 1; j > 0; --j )
		if ( a[j] < a[j-1] )  swap(a[j], a[j-1]);  // Result: a[0] == min

	for ( size_t i = 2; i < a.size(); ++i )
	{
		auto tmp = a[i];
		size_t j = i;
		for ( ; tmp < a[j-1]; --j )  a[j] = a[j-1];
		a[j] = tmp;
	}
}



#include <vector>
template void BubbleSort0(std::vector<int>&, std::less<int>);
template void BubbleSort0(std::vector<int>&, std::greater<int>);
template void BubbleSort1(std::vector<int>&);
template void BubbleSort2(std::vector<int>&);
template void SelectionSort(std::vector<int>& a);
template void InsertionSort1(std::vector<int>& a);
template void InsertionSort2(std::vector<int>& a);
template void InsertionSort3(std::vector<int>& a);

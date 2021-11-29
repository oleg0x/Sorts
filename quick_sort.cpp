#include <algorithm>

/*****************************************************************************
 * Quick sort (Tony Hoare in 1959):
 * Select a 'pivot' element from the array and partition the other elements 
 * into two sub-arrays, according to whether they are less or greater than 
 * the pivot; the sub-arrays are then sorted recursively. 
 * Not stable sort.
 * Complexity: O(NlogN) in average, ~(N^2)/2 exchanges in the worst-case.
 * Memory: O(logN) auxiliary.
 *****************************************************************************/



template <typename Container>
int Partition1(Container& a, int low, int high)
{
	using std::swap;
	int i = low;
	int j = high + 1;
	while ( true )
	{
		while ( a[++i] < a[low] )  // find item on left to swap
			if ( i == high )  break;
		while ( a[low] < a[--j] ) ;  // find item on right to swap
//			if ( j == low )  break;  // This is redundant
		if ( i >= j )  break;  // check if pointers cross
		swap(a[i], a[j]);
	}
	swap(a[low], a[j]);  // swap with partitioning item
	return j;  // return index of item now known to be in place
}



template <typename Container>
void QuickSort1(Container& a, int low, int high)
{
	if ( low < high )
	{
		int j = Partition1(a, low, high);
		QuickSort1(a, low, j - 1);
		QuickSort1(a, j + 1, high);
	}
}



template <typename Container>
void QuickSort1(Container& a)
{
	// Random shuffle for 'a' may be needed
	QuickSort1(a, 0, a.size() - 1);
}


//-----------------------------------------------


template <typename Container>
auto MedianOfThree(Container& a, int lo, int hi)
{
	using std::swap;
	int mid = (lo + hi) / 2;
	if ( a[mid] < a[lo] )  swap(a[lo], a[mid]);
	if ( a[hi] < a[lo] )   swap(a[lo], a[hi]);
	if ( a[hi] < a[mid] )  swap(a[mid], a[hi]);
	return a[mid];
}



template <typename Container>
int Partition2(Container& a, int low, int high)
{
	using std::swap;
//	auto pivot = a[(low + high) / 2];  // Instead of a[low]
	auto pivot = MedianOfThree(a, low, high);  // Instead of a[low]
	int i = low - 1;
	int j = high + 1;
	while ( true )
	{
		while ( a[++i] < pivot ) ; // find item on left to swap
		while ( pivot < a[--j] ) ; // find item on right to swap
		if ( i >= j )  return j;  // check if pointers cross
		swap(a[i], a[j]);
	}
}



template <typename Container>
void InsSort(Container& a, size_t low, size_t high)  // Use for small subarrays
{
	for ( size_t i = low + 1; i <= high; ++i )
		if ( a[i] < a[i-1] )
		{
			auto tmp = a[i];
			size_t j = i;
			for ( ; j != low && tmp < a[j-1]; --j )  a[j] = a[j-1];
			a[j] = tmp;
		}
}



template <typename Container>
void QuickSort2(Container& a, int low, int high)
{
	const int cutoff = 15;  // Cutoff to insertion sort for ≈ 10 items.
	if ( high <= low + cutoff )
	{
		InsSort(a, low, high);
		return;
	}
	int j = Partition2(a, low, high);
	QuickSort2(a, low, j);
	QuickSort2(a, j + 1, high);
}



template <typename Container>
void QuickSort2(Container& a)
{
	// Random shuffle for 'a' may be needed
	QuickSort2(a, 0, a.size() - 1);
}



#include <vector>
template void QuickSort1(std::vector<int>&);
template void QuickSort2(std::vector<int>&);

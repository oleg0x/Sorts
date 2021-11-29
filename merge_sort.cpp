#include <algorithm>
#include <cstddef>

/*****************************************************************************
 * Merge sort:
 * Divide array into two halves, recursively sort each half, merge two halves. 
 * Stable sort.
 * Complexity: O(NlogN); at most NlogN compares and 6NlogN array accesses, 
 * Memory: O(N) total with O(N) auxiliary.
 *****************************************************************************/



template <typename Container>
void Merge1(Container& a, Container& aux, size_t low, size_t mid, size_t high)
{
	for ( size_t k = low; k <= high; ++k )  aux[k] = a[k];
//	aux = a;  // This assignment is slower than previous loop
	size_t i = low;
	size_t j = mid + 1;
	for ( size_t k = low; k <= high; ++k )
	{
		if      ( i > mid )          a[k] = aux[j++];
		else if ( j > high )         a[k] = aux[i++];
		else if ( aux[j] < aux[i] )  a[k] = aux[j++];
		else                         a[k] = aux[i++];
	}
}



template <typename Container>
void MergeSort1(Container& a, Container& aux, size_t low, size_t high)
{
	if ( high <= low )  return;
	size_t mid = low + (high - low) / 2;
	MergeSort1(a, aux, low, mid);
	MergeSort1(a, aux, mid + 1, high);
	Merge1(a, aux, low, mid, high);
}



template <typename Container>
void MergeSort1(Container& a)
{
	Container aux(a);
	MergeSort1(a, aux, 0, a.size() - 1);
}



// Switch the role of the input and auxiliary array in each recursive call

template <typename Container>
void Merge2(Container& a, Container& aux, size_t low, size_t mid, size_t high)
{
	size_t i = low;
	size_t j = mid + 1;
	for ( size_t k = low; k <= high; ++k )
	{
		if      ( i > mid )      aux[k] = a[j++];
		else if ( j > high )     aux[k] = a[i++];
		else if ( a[j] < a[i] )  aux[k] = a[j++];
		else                     aux[k] = a[i++];
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
void MergeSort2(Container& a, Container& aux, size_t low, size_t high)
{
//	if ( high <= low + 6 )  { InsSort(a, low, high); return; }
	if (  low < high )
	{
		size_t mid = low + (high - low) / 2;
		MergeSort2(aux, a, low, mid);
		MergeSort2(aux, a, mid + 1, high);
//		if ( a[mid] <= a[mid+1] )  return;  // Stop if already sorted
		Merge2(aux, a, low, mid, high);
	}
}



template <typename Container>
void MergeSort2(Container& a)
{
	Container aux(a);
	MergeSort2(a, aux, 0, a.size() - 1);
}



// Bottom-up merge sort (non-recursive):
// Pass through array, merging subarrays of size 1, repeat for subarrays 
// of size 2, 4, 8, 16, ...

template <typename Container>
void MergeSort3(Container& a)  // Non-recursive version
{
	size_t n = a.size();
	Container aux(a);
	for ( size_t sz = 1; sz < n; sz *= 2 )
		for ( size_t low = 0; low < n - sz; low += 2*sz )
			Merge1(a, aux, low, low + sz - 1, std::min(low + 2*sz - 1, n - 1));
}



#include <vector>
template void MergeSort1(std::vector<int>&);
template void MergeSort2(std::vector<int>&);
template void MergeSort3(std::vector<int>&);

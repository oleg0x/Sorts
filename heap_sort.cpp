#include <algorithm>
#include <cstdint>

/*****************************************************************************
 * Heap sort:
 * Turn the array into a max heap, then repeatedly swaps the first value of 
 * the array with the last value, decreasing the range of 
 * values by one, and sift the new first value into its position in the heap.
 * In-place, not stable algorithm.
 * Complexity: O(NlogN)
 *****************************************************************************/



template <typename Container>
void Sink(Container& a, size_t k, size_t n)
{
	using std::swap;
	while ( 2*k + 1 <= n )
	{
		size_t j = 2*k + 1;  // Children of node at k are 2k+1 and 2k+2
		if ( j + 1 <= n && a[j] < a[j+1] )  ++j;
		if ( !(a[k] < a[j]) )  break;
		swap(a[k], a[j]);
		k = j;
	}
}



template <typename Container>
void HeapSort(Container& a)
{
	using std::swap;
	size_t n = a.size() - 1;

	// Create max-heap of the given container
	for ( int64_t k = n/2; k >= 0; --k )  Sink(a, k, n);
	
	while ( n > 0 )
	{
		swap(a[0], a[n]);
		Sink(a, 0, --n);
	}
}



#include <vector>
template void HeapSort(std::vector<int>&);

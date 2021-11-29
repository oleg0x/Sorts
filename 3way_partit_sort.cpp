#include <algorithm>

/*****************************************************************************
 * Dijkstra's 3-way partitioning sort.
 * Complexity: O(N) when only a constant number of distinct keys, 
 * O(NlogN) when all distinct.
 *****************************************************************************/



template <typename Container>
void ThreeWayPartitioningSort(Container& a, int low, int high)
{
	if ( high <= low )  return;
	using std::swap;
	int lt = low;
	int gt = high;
	auto v = a[low];
	int i = low;
	while ( i <= gt )
	{
		if      ( a[i] < v )  swap(a[lt++], a[i++]);
		else if ( a[i] > v )  swap(a[i], a[gt--]);
		else ++i;
	}
	ThreeWayPartitioningSort(a, low, lt - 1);
	ThreeWayPartitioningSort(a, gt + 1, high);
}



template <typename Container>
void ThreeWayPartitioningSort(Container& a)
{
	ThreeWayPartitioningSort(a, 0, a.size() - 1);
}



#include <vector>
template void ThreeWayPartitioningSort(std::vector<int>&);

#include <algorithm>
#include <cstddef>

/*****************************************************************************
 * Shell sort:
 * The method starts by sorting pairs of elements far apart from each other, 
 * then progressively reducing the gap between elements to be compared.
 * Not stable sort.
 * Complexity: the worst-case number of compares with the 3h+1 increments 
 * is O(N^(3/2)).
 *****************************************************************************/



template <typename Container>
void ShellSort(Container& a)
{
	using std::swap;
	const size_t n = a.size();
	size_t h = 1;
	for ( ; 3 * h + 1 < n; h = 3 * h + 1 ) ;  // Find h
	for ( ; h >= 1; h /= 3 )  // h-sort the container
		for ( size_t i = h; i < n; ++i )  // Insertion sort
			for ( size_t j = i; j >= h && a[j] < a[j-h]; j -= h )
				swap(a[j], a[j-h]);
}



#include <vector>
template void ShellSort(std::vector<int>&);

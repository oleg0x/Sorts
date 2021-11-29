#include <cstdint>
#include <vector>

/*****************************************************************************
 * Counting sort:
 * Count the number of objects that have each distinct key, then determine 
 * the positions of each key in the output sequence.
 * Complexity: O(N+R), where R is the range of the non-negative key values.
 *****************************************************************************/



template <typename Container>
void CountingSort1(Container& a)
{
	const uint32_t max = *max_element(a.begin(), a.end());
	std::vector<std::uint32_t> counts(max + 1, 0);
	for ( auto item : a )  ++counts[item];
	for ( std::uint32_t i = 0, k = 0; i <= max; ++i )
		for ( std::uint32_t j = 0; j < counts[i]; ++j )
			a[k++] = i;
}



template <typename Container>
void CountingSort2(Container& a)
{
	int min_elem = a[0];
	int max_elem = a[0];
	for ( uint32_t i = 1; i < a.size(); ++i )
	{
		if ( a[i] < min_elem )  min_elem = a[i];
		if ( a[i] > max_elem )  max_elem = a[i];
	}
	std::vector<std::uint32_t> counts(max_elem - min_elem + 1, 0);
	for ( int item : a )  ++counts[item - min_elem];
	for ( int i = min_elem, k = 0; i <= max_elem; ++i )
		for ( std::uint32_t j = 0; j < counts[i - min_elem]; ++j )
			a[k++] = i;
}



#include <vector>
template void CountingSort1(std::vector<int>&);
template void CountingSort2(std::vector<int>&);

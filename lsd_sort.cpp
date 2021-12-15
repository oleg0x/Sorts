#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

/*****************************************************************************
 * Least-significant-digit-first string sort (LSD string sort):
 * Consider characters from right to left. Stably sort using d-th
 * character as the key (using key-indexed counting).
 * Stable sort.
 * Complexity: 2*len*N, i.e. O(N) for len=const (20*N for ints)
 * Memory: N+R
 *****************************************************************************/



void LsdSort(vector<string>& a)  // Sort strings of equal length
{
	const int N = a.size();
	const int len = (N > 0 ? a[0].size() : 0);
	const int R = 256;  // Radix (ASCII)
	vector<string> aux(N);
	for ( int d = len - 1; d >= 0; --d )
	{
		vector<int> count(R+1, 0);
		for ( int i = 0; i < N; ++i )  count[a[i][d]+1]++;
		for ( int r = 0; r < R; ++r )  count[r+1] += count[r];
		for ( int i = 0; i < N; ++i )  aux[count[a[i][d]]++] = a[i];
		swap(a, aux);
	}
}


//-------------------------------------------------------------------


inline void Uint2Str(uint32_t n, string& str)
{
	for ( int8_t i = 9; i >= 0; --i )
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
}



vector<string> Uints2Strs(const vector<int>& v)
{
	string str(10, 0);  // 2 147 483 647 (10 digits)
	vector<string> res;
	for ( auto x : v )
	{
		Uint2Str(x, str);
		res.push_back(str);
	}
	return res;
}



template <typename Container>
void Print(const Container& c)
{
	if ( c.empty() )  cout << "Container is empty";
	for ( auto elem : c )  cout << elem << ' ';
	cout << '\n';
}


//-------------------------------------------------------------------


void TestSmallData()
{
	cout << "\n---------- " << __func__ << " ----------\n";

	vector<string> a;
	LsdSort(a);
	Print(a);
	assert( a == vector<string>() );

	a.push_back("yyy");
	LsdSort(a);
	Print(a);
	assert( a == vector<string>({"yyy"}) );

	a.push_back("xxx");
	LsdSort(a);
	Print(a);
	assert( a == vector<string>({"xxx", "yyy"}) );

	vector<string> b {"abcd", "dddd", "aaaa", "ffff", "bbbb", "eeee"};
	LsdSort(b);
	Print(b);
	assert( b == vector<string>({"aaaa", "abcd", "bbbb", "dddd", "eeee", "ffff"}) );

	cout << __func__ << " is OK.\n";
}



void Test1MlnUints()
{
	cout << "\n---------- " << __func__ << " ----------\n";

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<uint32_t> distr(0, numeric_limits<uint32_t>::max());

	constexpr uint32_t N = 1'000'000;
	vector<int> a(N);
	for ( uint32_t i = 0; i < N; ++i )  a[i] = distr(gen);
	vector<string> b(Uints2Strs(a));
	vector<string> copy_b(b);

	using namespace std::chrono;

	auto t1 = steady_clock::now();
	std::sort(a.begin(), a.end());
	auto t2 = steady_clock::now() - t1;
	cout << "std::sort: "
	     << duration_cast<milliseconds>(t2).count() << " ms\n";

	t1 = steady_clock::now();
	LsdSort(b);
	t2 = steady_clock::now() - t1;
	cout << "LsdSortUints: "
	     << duration_cast<milliseconds>(t2).count() << " ms\n";

	std::sort(copy_b.begin(), copy_b.end());
	assert( b == copy_b );

	cout << __func__ << " is OK.\n";
}



int main()
{
	const vector<int> v {0, 5, 42, 12345, 123456789, numeric_limits<int>::max()};
	Print(v);
	vector<string> s = Uints2Strs(v);
	Print(s);

	TestSmallData();
	Test1MlnUints();
}

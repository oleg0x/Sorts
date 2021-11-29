#include "sorts.h"

#include <cassert>
#include <chrono>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using namespace std;



template <typename Container>
void Print(const Container& c)
{
	for ( auto elem : c )  cout << elem << ' ';
	cout << '\n';
}



template <typename Container>
void TestSortsDurat( Container& c, bool need_duration = false,
                         uint16_t first_sort = 0, uint16_t last_sort = 0 )
{
	using namespace std::chrono;

	vector< pair<void (*)(Container&), string> > functions;
	functions.push_back( {BubbleSort1<Container>, "BubbleSort1"} );
	functions.push_back( {BubbleSort2<Container>, "BubbleSort2"} );
	functions.push_back( {SelectionSort<Container>, "SelectionSort"} );
	functions.push_back( {InsertionSort1<Container>, "InsertionSort1"} );
	functions.push_back( {InsertionSort2<Container>, "InsertionSort2"} );
	functions.push_back( {InsertionSort3<Container>, "InsertionSort3"} );
	functions.push_back( {ShellSort<Container>, "ShellSort"} );
	functions.push_back( {HeapSort<Container>, "HeapSort"} );
	functions.push_back( {MergeSort1<Container>, "MergeSort1"} );
	functions.push_back( {MergeSort2<Container>, "MergeSort2"} );
	functions.push_back( {MergeSort3<Container>, "MergeSort3"} );
	functions.push_back( {QuickSort1<Container>, "QuickSort1"} );
	functions.push_back( {QuickSort2<Container>, "QuickSort2"} );
	functions.push_back( {ThreeWayPartitioningSort<Container>, "ThreeWayPartitioningSort"} );
	functions.push_back( {CountingSort2<Container>, "CountingSort2"} );

	Container sorted_c {c};
	auto t = steady_clock::now();
	std::sort(sorted_c.begin(), sorted_c.end());
	auto sort_t = steady_clock::now() - t;
	if ( !need_duration )  Print(sorted_c);  // Debug print
		
	for ( uint16_t i = first_sort; i <= last_sort; ++i )
	{
		Container tmp {c};
		auto t = steady_clock::now();
		functions[i].first(tmp);
		auto dur = steady_clock::now() - t;
		assert( tmp == sorted_c );
		if ( need_duration )  // Comment this line to show all functions
			cout << functions[i].second << ": " 
			     << duration_cast<milliseconds>(dur).count() << " ms\n";
	}
	if ( need_duration )
	{
		auto t = steady_clock::now();
		std::stable_sort(c.begin(), c.end());
		auto stable_sort_t = steady_clock::now() - t;
		cout << "std::stable_sort: "
		     << duration_cast<milliseconds>(stable_sort_t).count() << " ms\n";
		cout << "std::sort: " 
		     << duration_cast<milliseconds>(sort_t).count() << " ms\n";
	}
}



void ShortTests()
{
	cout << "---------- " << __func__ << " ----------\n";

	vector<int> a1 {'x'};
	TestSortsDurat<vector<int>>(a1);

	vector<int> a2 {-2, 3};
	TestSortsDurat<vector<int>>(a2);

	vector<int> a3 {2, -3};
	TestSortsDurat<vector<int>>(a3);

	vector<int> a4 {5, 8, 2};
	TestSortsDurat<vector<int>>(a4);
	
	BubbleSort0(a4);  // Template argument deduction with template default parameter
	Print(a4);
	BubbleSort0(a4, std::greater<int>());  // Template argument deduction
	Print(a4);
	BubbleSort0< int, vector, greater<int> >(a4, greater<int>());  // Full version
	Print(a4);
	
	vector a5 {2, 8, 5};
	TestSortsDurat(a5);
	
	vector<int> a6 {'c', 'z', 'p', 't', 'z', 'o', 'w', 'e', 'c', 'a'};
	TestSortsDurat<vector<int>>(a6);
	
	vector<int> a7 {7, -2,  0, -5, 7, 1, 7, 4, -2, 8, 0, 9, 1, -4, -5};
	TestSortsDurat(a7);  // Template argument deduction
	
//	deque<string> a8 { "foo", "bar", "zoo", "000", "home", "all", "tree", "123"};
//	TestSortsDurat<deque<string>>(a8, true, 7);

	cout << __func__ << " is OK.\n";
}



void LongTestAll()
{
	cout << "\n---------- " << __func__ << " ----------\n";

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distr;
	
	constexpr uint32_t n = 10'000;
	vector<int> data;
	data.reserve(n);
	
	for ( uint32_t i = 0; i < n; ++i )  data.push_back(distr(gen));
	TestSortsDurat(data, true, 0, 13);

	cout << __func__ << " is OK.\n";
}



void TimeCmpTest()
{
	cout << "\n---------- " << __func__ << " ----------\n";

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distr;

	constexpr uint32_t n = 500'000;
	vector<int> data;
	
	data.reserve(n);
	for ( uint32_t i = 0; i < n; ++i )  data.push_back(distr(gen));
	TestSortsDurat(data, true, 6, 13);
	
	data.clear();
	data.reserve(2*n);
	distr.param( uniform_int_distribution<int>::param_type {0, 500} );
	for ( uint32_t i = 0; i < 2*n; ++i )  data.push_back(distr(gen));
	TestSortsDurat(data, true, 6, 14);

	cout << __func__ << " is OK.\n";
}

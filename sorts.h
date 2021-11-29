#pragma once

#include <functional>



template <typename T, template<typename> typename Container, typename Compare = std::less<T>>
void BubbleSort0(Container<T>& a, Compare comp = Compare());

template <typename Container>
void BubbleSort1(Container& a);

template <typename Container>
void BubbleSort2(Container& a);

template <typename Container>
void SelectionSort(Container& a);

template <typename Container>
void InsertionSort1(Container& a);

template <typename Container>
void InsertionSort2(Container& a);

template <typename Container>
void InsertionSort3(Container& a);

template <typename Container>
void ShellSort(Container& a);

template <typename Container>
void HeapSort(Container& a);

template <typename Container>
void MergeSort1(Container& a);

template <typename Container>
void MergeSort2(Container& a);

template <typename Container>
void MergeSort3(Container& a);

template <typename Container>
void QuickSort1(Container& a);

template <typename Container>
void QuickSort2(Container& a);

template <typename Container>
void ThreeWayPartitioningSort(Container& a);

template <typename Container>
void CountingSort1(Container& a);

template <typename Container>
void CountingSort2(Container& a);

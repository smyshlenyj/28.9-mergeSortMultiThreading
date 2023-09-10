#include <iostream>
#include <chrono>
#include <random>
#include <future>
#include <thread>

void merge(int* arr, int l, int m, int r)
{
	int nl = m - l + 1;
	int nr = r - m;
	int* left = new int[nl];
	int* right = new int[nr];

	for (int i = 0; i < nl; i++)
		left[i] = arr[l + i];
	for (int j = 0; j < nr; j++)
		right[j] = arr[m + 1 + j];

	int i = 0, j = 0;
	int k = l;

	while (i < nl && j < nr)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < nl)
	{
		arr[k] = left[i];
		i++;
		k++;
	}

	while (j < nr)
	{
		arr[k] = right[j];
		j++;
		k++;
	}
}

void mergeSort(int* arr, int l, int r)
{
	int m = (l + r - 1) / 2;
	if (l < r)
	{
		if (m - l > 4'000'000)
		{
			std::future <void> left = std::async(std::launch::async, mergeSort, arr, l, m);
			std::future <void> right = std::async(std::launch::async, mergeSort, arr, m + 1, r);
			left.get();
			right.get();
			merge(arr, l, m, r);
		}
		else
		{
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}
}

int main()
{
	bool printArray = false;
	srand(0);
	int n = 9'999'999;
	int* array = new int[n];
	for (int i = 0; i < n; i++)
		array[i] = rand() % 50000;

	if (printArray)
	{
		std::cout << "\nUnsorted array:" << std::endl;
		for (int i = 0; i < n; ++i)
			std::cout << array[i] << " ";
		std::cout << std::endl;
	}
	time_t start, end;

	time(&start);
	mergeSort(array, 0, n - 1);
	time(&end);

	int seconds = difftime(end, start);

	if (printArray)
	{
		std::cout << "Sorted array:" << std::endl;
		for (int i = 0; i < n; ++i)
			std::cout << array[i] << " ";
	}
	std::cout << "\nTime elapsed: " << seconds << std::endl;
	delete[] array;
	return 0;
}
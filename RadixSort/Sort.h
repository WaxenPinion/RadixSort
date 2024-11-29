#pragma once

#include <vector>

//std::vector<int> RadixSortInt(std::vector<int>& vec);

template <typename T>
std::vector<T> radixSort(std::vector<T>& vec) {

	std::vector<T> result(vec);
	std::vector<std::vector<T>> bin(2, std::vector<T>());

	const int size = sizeof(T) * 8;

	for (int i = 0; i < size; ++i) {

		for (T& el : result) {

			const unsigned char tmp = *(((char*)&el) + (i / 8));
			int j = (tmp & (1 << (i % 8))) ? 1 : 0;
			//- lsd, size - i - 1 instead of i - msd
			bin.at(j).push_back(el);

		}

		result.clear();
		for (std::vector<T>& digit : bin) { // int 
			for (T& el : digit) {
				result.push_back(el);
			}
			digit.clear();
		}

	}

	return result;
}
// O(N)*O(size)*O(1) + O(1) + O(N)*O(size) = O(N*size)

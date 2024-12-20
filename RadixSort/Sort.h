// Sort.h

#pragma once


#include <vector>

template <typename T>
void radixSort(std::vector<T>&vec) {

	std::vector<std::vector<T>> bin(2, std::vector<T>());

	const int size = sizeof(T) * 8;

	for (int i = 0; i < size; ++i) {

		for (T& el : vec) {

			const unsigned char tmp = *(((char*)&el) + (i / 8));
			int j = (tmp & (1 << (i % 8))) ? 1 : 0;
			//- lsd, size - i - 1 instead of i - msd
			bin.at(j).push_back(el);

		}

		vec.clear();
		for (std::vector<T>& digit : bin) {
			for (T& el : digit) {
				vec.push_back(el);
			}
			digit.clear();
		}

	}

}

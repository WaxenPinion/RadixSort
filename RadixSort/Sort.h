#pragma once

#include <vector>

std::vector<int> RadixSort(std::vector<int>& vec);

namespace v2 {

	template <typename T>
	std::vector<T> RadixSort(std::vector<T>& vec) {

		std::vector<T> result(vec);
		std::vector<std::vector<T>> bin(2, std::vector<T>());

		const int size = sizeof(T) * 8;

		for (int i = 0; i < size; ++i) {

			for (T& el : result) {
				const unsigned char tmp = *(((char*)&el) + (i / 8));
				int j = (tmp & (1 << (i % 8))) ? 1 : 0;
				//- lsd, max_lenght - i - 1 instead of i - msd
				bin.at(j).push_back(el);

			}

			result.clear();
			for (std::vector<T>& digit : bin) {
				for (T& el : digit) {
					result.push_back(el);
				}
				digit.clear();
			}
		}

		return result;
	}

}
#include "Sort.h"

#include <iostream>
#include <vector>


using namespace std;

/*vector<int> RadixSort(vector<int>& vec) {

	int base = 10;
	vector<int> result(vec);
	vector<vector<int>> tmp(base, vector<int>());

	int max = vec.at(0);
	for (int el : vec) {
		if (el > max) max = el;
	}
	int max_lenght = static_cast<int>(log(max)/log(base)) + 1;
	
	for (int i = 0; i < max_lenght; ++i) {//sizeof(int) * 8; ++i) { max_length
		
		for (int& el : result) {
			int j = (el / static_cast<int>(pow(base, i))) % base; //- lsd, max_lenght - i - 1 instead of i - msd
			tmp.at(j).push_back(el);

		}
		
		result.clear();
		for (vector<int>& digit : tmp) {
			for (int& el : digit) {
				result.push_back(el);
			}
			digit.clear();
		}
	}

	return result;
} // now do bit by bit for anything*/

int main() {

	//std::cout << "Hello, World!" << std::endl;

	//std::cout << log(15)/log(10) << std::endl;

	vector<int> test{234, 1, 3, 34, 235, 5435, 1435, 5, 10, 14, 90};

	vector<int> result{ RadixSort(test) };

	for (int& el : result) {
		cout << el << ", ";
	}

	//int i = 0;
	//std::cin >> i;

	return EXIT_SUCCESS;
}
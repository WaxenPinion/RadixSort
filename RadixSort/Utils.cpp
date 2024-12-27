// Utils.cpp

#include "Utils.h"

#include <random>
#include <vector>

using namespace std;

int generateRandomInt(int min, int max) {
	static std::random_device rd{};
	static std::default_random_engine drf{ rd()};
	
	if (max - min + 1 == 0 or max < min) return drf();
	return drf() % (max - min + 1) + min;
}


vector<int> generateRandomVec(int size, int min, int max) {
	if (size <= 0) size = 10;
	vector<int> result{};
	for (int i = 0; i < size; ++i) result.push_back(generateRandomInt(min, max));

	return result;
}

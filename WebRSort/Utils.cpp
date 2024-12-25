// Utils.cpp

#include "Utils.h"

#include <random>


int generateRandomInt(int min, int max) {
	static std::random_device rd{};
	static std::default_random_engine drf{ rd()};
	
	if (max - min + 1 == 0) return drf();
	return drf() % (max - min + 1) + min;
}

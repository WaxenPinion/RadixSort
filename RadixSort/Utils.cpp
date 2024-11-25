#include "Utils.h"

#include <random>
#include <sstream>
#include <iostream>
#include <vector>
//#include <vector>


int generateRandomInt(int min, int max) {
	static std::random_device r{};
	static std::default_random_engine drf{r()};
	//int b = drf() % (max - min) + min;
	return drf() % (max + 1 - min) + min;
}

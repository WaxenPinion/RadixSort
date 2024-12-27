//ConsoleTests.cpp

#include "ButtonLogic.hpp"
#include "Consoleio.h"
#include "Utils.h"
#include "Sort.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

bool testAdd(int count) {

	sf::Http http{ "localhost", 8000 };

	for (int i = 0; i < count; ++i) {
		
		vector<int> tmp = generateRandomVec(0, 1, 100);
		stringstream stream{};
		stream << tmp;

		sf::Http::Response response = sendPostRequest(http, "add/" + stream.str());
		if (response.getStatus() != sf::Http::Response::Ok) return false;
	}
	
	return true;
}

bool testDelete(int count) {

	sf::Http http{ "localhost", 8000 };

	for (int i = 0; i < count; ++i) {

		vector<int> tmp = generateRandomVec(0, 1, 100);
		stringstream stream{};
		stream << tmp;

		sf::Http::Response response = sendPostRequest(http, "delete/1");
		if (response.getStatus() != sf::Http::Response::Ok) return false;
	}

	return true;
}


bool testSort(int count) {

	sf::Http http{ "localhost", 8000 };
	sf::Http::Response response = sendGetRequest(http, "/?all");
	if (response.getStatus() != sf::Http::Response::Ok) return false;
	
	vector<sf::String> arrays{ splitAllArrays(response.getBody()) };

	size_t part_size = arrays.size() / count;

	if (part_size < 1) return false;

	for (size_t i = 0; i < count; ++i) {

		size_t j = 0;
		if (part_size > 1) j = generateRandomInt(0, part_size - 1);

		sf::String tmp{ sortStringArray(arrays.at(i * part_size + j)) };
		//cout << string(tmp);

	}

	return true;
}


bool testFunction(int count, bool(*func)(int)) {
	auto start = std::chrono::high_resolution_clock::now();
	bool result = func(count);
	auto end = std::chrono::high_resolution_clock::now();

	if (!result) {
		cout << "Тест не пройден" << endl;
		return result;
	}

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

	cout << "Тест пройден" << endl;
	cout << "Время выполнения: " << duration.count() << " секунд" << endl;

	return result;
}


int main() {

	SetCP ru{ SetCP::RU };

	vector<int> test_counts{ 100, 1000, 10000 };
	for (int count : test_counts) {
		cout << "Тест добавление " << count << endl;
		if(!testFunction(count, testAdd)) break;
		cout << "Тест сортировка " << count << endl;
		testFunction(100, testSort);
		cout << "Тест удаление " << count << endl;
		testFunction(count, testDelete);
	}

	return EXIT_SUCCESS;
}

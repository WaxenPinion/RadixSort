


#include "ButtonLogic.hpp"
#include "Consoleio.h"
#include "Utils.h"

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


int measureExecutionTime(int count, bool(*func)(int)) {
	auto start = std::chrono::high_resolution_clock::now();
	bool res = func(count);
	if (!res) throw res;
	auto end = std::chrono::high_resolution_clock::now();

	auto int_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	return int_s.count();
}


int main() {

	SetCP ru{ SetCP::RU };

	cout << "Тест добавление 100" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(100, testAdd)
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

	cout << "Тест удаление 100" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(100, testDelete) 
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

	cout << "Тест добавление 1000" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(1000, testAdd)
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

	cout << "Тест удаление 100" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(1000, testDelete)
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

	cout << "Тест добавление 10000" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(10000, testAdd)
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

	cout << "Тест удаление 10000" << endl;
	try {
		cout << "Время выполнения: " << measureExecutionTime(10000, testDelete)
			<< " милисекунд" << endl;
	}
	catch (bool) {
		cout << "Тест не пройден" << endl;
	}

}

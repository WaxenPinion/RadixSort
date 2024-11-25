#include "Sort.h"
#include "Menu.h"
#include "Utils.h"
#include "Consoleio.h"

#include <iostream>
#include <vector>


using namespace std;


/*class A {
public:
	A() {
		cout << "created" << endl;
	};
	~A() {
		cout << "destroyed" << endl;
	}
	void print() {
		cout << m_int << endl;
	}

	int m_int{ 10 };
};

union Buffer {
	int integer;
	A vec;
	~Buffer() {}
};*/


/*bool checkEmpty(std::vector<int>& vec) {
	return !vec.empty();
}*/
vector<int> getRandomVector(vector<int>& vec) {

	int count = input::getInt(1, 1000, "Число случайных чисел: ");
	int min = input::getInt("Минимальное: ");
	int max = input::getInt(min, "Максимальное: ");

	vector<int> res{};
	for (int i = 0; i < count; ++i) {
		res.push_back(generateRandomInt(min, max));
	}

	return res;
}


int main() {

	SetCP ru{ 1251 };

	/*Buffer buf{2};
	//vector<int> vec{ 3,5 };
	{
		buf.vec = A();
	}
	buf.vec.print();
	buf.integer = 34322;
	buf.vec.print();*/

	//std::cout << "Hello, World!" << std::endl;

	//std::cout << log(15)/log(10) << std::endl;
	//MenuPtr p{};
	//p.reset();
	//cout << static_cast<bool>(Menu::makeEnd());

	/*/vector<int> test{234, 1, 3, 34, 235, 5435, 1435, 5, 10, 14, 90};

	vector<int> result{ RadixSort(test) };

	for (int& el : result) {
		cout << el << ", ";
	}*/

	auto condition = [](vector<int>& vec) { return !vec.empty(); };

	MenuController contr{};

	OptionMenu main{ msg::title::main }, input_choice{ msg::title::input_choice };
	InputMenu input{ msg::title::input };
	OutputMenu output{ msg::title::output };
	ClearMenu clear{ "Массив очищен." };
	ProcessMenu proc{ msg::title::sort, v2::RadixSort<int> }, 
		random{ "Массив отсортирован", getRandomVector};
	//proc.setFunction(RadixSort);
	//proc.setFunction(random_f);

	main.addOption(msg::option::input, &input_choice)
		.addOption(msg::option::show , &output, condition)
		.addOption(msg::option::clear, &clear , condition)
		.addOption(msg::option::sort , &proc  , condition)
		.addOption(msg::option::exit);
	input_choice.addOption(msg::option::manual_input   , &input)
				.addOption(msg::option::from_file      , &main)//change
				.addOption(msg::option::generate_random, &random)
				.addOption(msg::option::return_to_main , &main);
	input.setNext(&main);
	random.setNext(&main);

	contr.start(&main);

	return EXIT_SUCCESS;
}
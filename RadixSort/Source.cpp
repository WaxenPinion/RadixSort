#include "Sort.h"
#include "Menu.h"
#include "Utils.h"
#include "Consoleio.h"

#include <iostream>
#include <vector>


using namespace std;

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

	auto condition = [](vector<int>& vec) { return !vec.empty(); };

	MenuController contr{};

	OptionMenu main{ msg::title::main }, input_choice{ msg::title::input_choice };
	InputMenu input{ msg::title::input };
	OutputMenu output{ msg::title::output };
	ClearMenu clear{ "Массив очищен." };
	ProcessMenu proc{ "Массив отсортирован", radixSort<int> },
		random{ msg::title::random, getRandomVector};

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
// Source.cpp
// РПС
// Лабораторная работа № 2.
// Студент группы 434, Пшеничников Максим Юрьевич. 2024 год

#include "Consoleio.h"
#include "Fileio.h"
#include "Menu.h"
#include "Sort.h"
#include "Utils.h"

#include <iostream>
#include <vector>

enum FileOption {
	rewrite,
	input_another_path,
	cancel
};

using namespace std;


void getRandomVector(vector<int>& vec) {

	int count = input::getInt(1, 1000, msg::input::random_count);
	int min = input::getInt(msg::input::random_min);
	int max = input::getInt(min + 1, msg::input::random_max);

	vec.clear();
	for (int i = 0; i < count; ++i) {
		vec.push_back(generateRandomInt(min, max));
	}

}


void getInput(vector<int>& vec) {
	cin >> vec;
}


void clearVec(vector<int>& vec) {
	vec.clear();
}


void show(vector<int>& vec) {
	output::showVector(cout, vec);
}


void getFromFile(vector<int>& vec) {

	while (true) {

		string file_path{ input::getString(msg::input::file_path) };

		try {
			fileio::add(vec, file_path);
			break;
		}
		catch (msg::Msg error) {
			cout << endl << error << endl;
		}

	}

	cout << msg::reading_completed << endl;
}


void saveToFile(vector<int>& vec) {

	using namespace fileio;

	while (true) {

		cout << endl;

		string path{ input::getString(msg::input::file_path) };

		switch (checkFileState(path))
		{
		case is_file:

			cout << endl << msg::file_already_exists << endl << endl;
			cout << endl << msg::menu_header << endl;
			output::showOptions(msg::rewrite_options);

			switch (input::getOption(msg::rewrite_options.size()))
			{
			case rewrite:
				if (!checkFileRewriteable(path)) {
					cout << endl << msg::error::cant_write << endl;
					continue;
				}
				break;
			case input_another_path:
				continue;
			case cancel:
				return;
			}

			__fallthrough;
		case is_directory:
		case doesnt_exist:
			try {
				save(vec, path);
				cout << endl << msg::save_completed << endl;
				return;
			}
			catch (msg::Msg error) {
				cout << error << endl;
				continue;
			}
		case cant_exist:
			cout << endl << msg::error::file_cant_exist << endl;
			continue;
		case is_special:
			cout << endl << msg::error::cant_access << endl;
			continue;
		}

	}

}


int main() {

	SetCP ru{ SetCP::RU };

	auto condition = [](vector<int>& vec) { return !vec.empty(); };

	MenuController contr{};

	OptionMenu main{ msg::title::main }, input_choice{ msg::title::input_choice };
	ProcessMenu output{ msg::title::output,  show },
				input{  msg::title::input,   getInput },
				clear{  msg::title::cleared, clearVec },
				proc{   msg::title::sorted,  radixSort<int> },
				random{ msg::title::random,  getRandomVector },
				file_input{  msg::title::file_input, getFromFile },
				file_output{ msg::title::file_output, saveToFile };

	main.addOption(msg::option::input, &input_choice)
		.addOption(msg::option::show, &output, condition)
		.addOption(msg::option::clear, &clear, condition)
		.addOption(msg::option::sort, &proc, condition)
		.addOption(msg::option::save, &file_output, condition)
		.addOption(msg::option::exit);

	input_choice.addOption(msg::option::manual_input   , &input)
				.addOption(msg::option::from_file      , &file_input)
				.addOption(msg::option::generate_random, &random)
				.addOption(msg::option::return_to_main , &main);

	input.setNext(&main);
	random.setNext(&main);

	contr.start(&main);

	return EXIT_SUCCESS;
}
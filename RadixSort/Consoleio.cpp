// Console.cpp
// Контрольная работа № 2.
// Наследование.
// Студент группы 4307, Пшеничников Максим Юрьевич. 2024 год

#include "Consoleio.h"
#include "Message.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;


namespace input {

	inline static void clearInputStream() {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	int getInt(msg::Msg& msg) {

		int output{};

		while (true) {

			cout << msg;
			cin >> output;

			if (!cin.fail()) {
				break;
			}

			cin.clear();
			clearInputStream();
			cout << msg::error::wrong_input << endl;

		}

		clearInputStream();
		return output;
	}


	/*int getInt(int min, msg::Msg& msg) {

		int output{ getInt(msg) };

		while (output < min) {
			cout << msg::error::wrong_input << endl;
			output = getInt(msg);
		}

		return output;
	}*/


	int getInt(int min, int max, msg::Msg& msg) {

		int output{ getInt(msg) };

		while (output < min or output > max) {
			cout << msg::error::wrong_input << endl;
			output = getInt(msg);
		}

		return output;
	}


	string getString(msg::Msg& msg) {
		cout << msg;
		string output{};
		getline(cin >> ws, output);
		cin.clear();
		return output;
	}


	string getWord(msg::Msg& msg) {
		cout << msg;
		string output{};
		cin >> output;
		clearInputStream();
		return output;
	}


	int getOption(size_t options_count) {

		//output::showOptions(header, options);

		return getInt(1, static_cast<int>(options_count), msg::input::choice) - 1;
	}


	/*string getFilePath() {
		string output{ getString(msg::input::file_path) };
		while (output == "?") {
			output::showFileInformation();
			output = input::getString(msg::input::file_path);
		}

		return output;
	}*/

} // namespace input

namespace output {

	void showOptions(msg::Msg& header, msg::MsgVector& options) {

		cout << header << endl;

		size_t index{ 0 };
		for (const auto& option : options) {
			cout << "  " << ++index << " - " << option << endl;
		}

	}


	void showOptions(msg::Msg& header, msg::MsgVector& options, std::vector<size_t> to_show) {

		cout << header << endl;

		size_t index{ 0 };
		for (size_t i : to_show) {
			cout << "  " << ++index << " - " << options.at(i) << endl;
		}

	}


	/*void showAddition(size_t old, size_t _new) {
		size_t delta{ _new - old };
		cout << endl << delta << " ";
		if (delta != 11 and delta % 10 == 1) cout << msg::added_singular;
		else cout << msg::added_plural;
		cout << endl;
	}


	void showInformation() {
		cout << msg::info::greating << endl;
		cout << msg::info::cw2 << endl << endl;
		cout << msg::info::task << endl;
	}


	void showFileInformation() {
		using namespace msg::employee;

		cout << endl << msg::info::file << endl;

		for (size_t i{ 0 }; i < types.size(); ++i) {
			cout << types[i] << " - " << type_letters[i] << " - " << string_structures[i] << endl;
		}
		cout << msg::info::file_end << endl << endl;
	}


	void showPayment(EmployeeVector& employees) {

		cout << endl << msg::title::payment << endl;

		size_t total{ 0 }, index{ 0 };
		for (const auto& employee : employees) {

			cout << msg::employee::header << ++index << " - ";
			cout << employee->calculatePayment() << endl;
			total += employee->calculatePayment();

		}

		cout << msg::total << total << endl;
	}*/

} // namespace output

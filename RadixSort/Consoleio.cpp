// Consoleio.cpp

#include "Consoleio.h"
#include "Message.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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


	int getInt(int min, msg::Msg& msg) {

		int output{ getInt(msg) };

		while (output < min) {
			cout << msg::error::wrong_input << endl;
			output = getInt(msg);
		}

		return output;
	}


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

		return getInt(1, static_cast<int>(options_count), msg::input::choice) - 1;
	}

} // namespace input

namespace output {

	void showOptions(msg::MsgVector& options) {

		size_t index{ 0 };
		for (const auto& option : options) {
			cout << "  " << ++index << " - " << option << endl;
		}

	}

} // namespace output


istream& operator>>(istream& in, vector<int>& vec) {

	string buf{};
	getline(in, buf, '\n');
	stringstream stream{};
	stream << buf;

	int tmp = 0;
	while (stream >> tmp) {
		vec.push_back(tmp);
	}

	return in;
}


ostream& operator<<(ostream& out, const vector<int>& vec) {
	output::showVector<int>(out, vec, " ", "", "");
	return out;
}

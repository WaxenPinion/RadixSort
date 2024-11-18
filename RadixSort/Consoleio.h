// Consoleio.h
// Контрольная работа № 2.
// Наследование.
// Студент группы 4307, Пшеничников Максим Юрьевич. 2024 год

#pragma once

#include "Message.h"

#include <vector>
#include <string>
#include <iostream>

namespace input {

	int getInt(msg::Msg& msg = "");
	//int getInt(int min, msg::Msg& msg = "");
	int getInt(int min, int max, msg::Msg& msg = "");

	std::string getString(msg::Msg& msg = "");
	std::string getWord(msg::Msg& msg = "");

	int getOption(size_t options_count);

	//std::string getFilePath();

} // namespace input


namespace output {

	void showOptions(msg::Msg& header, msg::MsgVector& options);
	void showOptions(msg::Msg& header, msg::MsgVector& options, std::vector<size_t> to_show);

	template <typename T>
	void showVector(std::vector<T>& vec, msg::Msg& header, msg::Msg& sep = ", ",
		msg::Msg& start = "[ ", msg::Msg& end = " ]") {
		
		std::cout << header << std::endl << start;
		for (size_t i = 0; i < vec.size() - 1; ++i) {
			std::cout << vec.at(i) << sep;
		}
		std::cout << vec.back() << end << std::endl;

	}

	//void showAddition(size_t old, size_t _new);
	//void showInformation();
	//void showFileInformation();
	
} // namespace output

std::istream& operator>>(std::istream& in, std::vector<int>& vec);

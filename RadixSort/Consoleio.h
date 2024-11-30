// Consoleio.h
// РПС
// Лабораторная работа № 2.
// Студент группы 434, Пшеничников Максим Юрьевич. 2024 год

#pragma once

#include "Message.h"

#include <vector>
#include <string>
#include <iostream>

namespace input {

	int getInt(msg::Msg& msg = "");
	int getInt(int min, msg::Msg& msg = "");
	int getInt(int min, int max, msg::Msg& msg = "");

	std::string getString(msg::Msg& msg = "");
	std::string getWord(msg::Msg& msg = "");

	int getOption(size_t options_count);

} // namespace input


namespace output {

	void showOptions(msg::MsgVector& options);

	template <typename T>
	concept Outputable = requires(T a) {
		std::cout << a;
	};

	template <Outputable T>
	void showVector(std::ostream& out, const std::vector<T>& vec,
		msg::Msg& sep = ", ", msg::Msg& start = "[ ", msg::Msg& end = " ]") {
		
		out << start;
		for (size_t i = 0; i < vec.size() - 1; ++i) {
			out << vec.at(i) << sep;
		}
		out << vec.back() << end << std::endl;

	}
	
} // namespace output


std::istream& operator>>(std::istream& in, std::vector<int>& vec);
std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec);

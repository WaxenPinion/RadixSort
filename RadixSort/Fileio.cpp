// Fileio.cpp
// Контрольная работа № 3.
// Классы потоков ввода-вывода.
// Студент группы 4307, Пшеничников Максим Юрьевич. 2024 год

#include "Fileio.h"
#include "Message.h"

#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace fileio {

	FileState checkFileState(const string& file_path) {
		try {
			if (fs::is_regular_file(file_path)) return is_file;
			else if (fs::is_directory(file_path)) return is_directory;
			else if (fs::exists(file_path)) return is_special;
			else return doesnt_exist;
		}
		catch (fs::filesystem_error) {
			return cant_exist;
		}
		return doesnt_exist;
	}


	bool checkFileRewriteable(const std::string& file_path) {
		return !!ofstream(file_path, ios::app);
	}


	void add(string& text, const string& file_path) {

		switch (checkFileState(file_path))
		{
		case doesnt_exist:
			throw msg::error::wrong_input;//no_file;
		case cant_exist:
			throw msg::error::wrong_input; //file_cant_exist;
		default:
			break;
		}

		ifstream fin{ file_path };

		if (!fin) throw msg::error::wrong_input; //cant_access;

		string buf{};
		getline(fin, buf, '\0');
		(text += '\n') += buf;

	}


	void save(const string& text, const string& file_path) {

		ofstream fout{ file_path };

		if (!fout) throw msg::error::wrong_input; //cant_create;

		fout << text;

	}

	void save(const vector<string>& vec, const string& dir_path) {

		size_t index{ 0 };
		for (const auto& text : vec) {

			string d_path{ (dir_path + "dialog_") + to_string(index + 1) + ".txt" };

			if (checkFileState(d_path) != doesnt_exist)
				throw msg::error::wrong_input; //file_already_exists;

			save(text, d_path);

			++index;
		}

	}

} // namespace fileio



// Fileio.cpp

#include "Consoleio.h"
#include "Fileio.h"
#include "Message.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

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


	void add(std::vector<int>& vec, const string& file_path) {

		switch (checkFileState(file_path))
		{
		case doesnt_exist:
			throw msg::error::no_file;
		case cant_exist:
			throw msg::error::file_cant_exist;
		default:
			break;
		}

		ifstream fin{ file_path };

		if (!fin) throw msg::error::cant_access;

		string buf{};
		getline(fin, buf, '\0');
		fin >> vec;

	}


	void save(const std::vector<int>& vec, const string& file_path) {

		ofstream fout{ file_path };

		if (!fout) throw msg::error::cant_create;

		fout << vec;

	}

} // namespace fileio



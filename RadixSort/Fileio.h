// Fileio.h
// Контрольная работа № 3.
// Классы потоков ввода-вывода.
// Студент группы 4307, Пшеничников Максим Юрьевич. 2024 год

#pragma once

#include <string>
#include <vector>


namespace fileio {

	enum FileState {
		doesnt_exist,
		is_file,
		is_directory,
		cant_exist,
		is_special,
	};

	FileState checkFileState(      const std::string& file_path);
	bool      checkFileRewriteable(const std::string& file_path);

	void add(       std::string& text, const std::string& file_path);
	void save(const std::string& text, const std::string& file_path);

	void save(const std::vector<std::string>& vec, const std::string& dir_path);

} // namespace fileio

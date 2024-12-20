// Fileio.h

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

	void add(		std::vector<int>& vec, const std::string& file_path);
	void save(const std::vector<int>& vec, const std::string& file_path);

	//void save(const std::vector<std::string>& vec, const std::string& dir_path);

} // namespace fileio

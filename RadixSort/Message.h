#pragma once

#include <string>
#include <vector>

namespace msg {

	using Msg = const std::string;
	using MsgVector = const std::vector<std::string>;

	namespace title {

		const size_t size = 26; // title size

		inline Msg centerize(Msg& title) {
			std::string front{}, end{};
			size_t n{ size - title.size() };
			for (size_t i{ 0 }; i < n / 2; ++i) {
				front += "-";
				end += "-";
			}
			if (n % 2 == 1) front += "-";
			return front + title + end;
		}

		Msg main{ centerize("Главное меню") };
		Msg	add{ centerize("Добавление") };
		Msg show{ centerize("Текст") };
		Msg save{ centerize("Сохранение") };
		Msg dialogs{ centerize("Диалоги") };

	} // namespace title

	namespace input {

		Msg choice{ "Ваш выбор: " };
		//Msg file_path{ "Введите путь к файлу: " };
		//Msg text{ "Введите текст. Ввод оканчивается $." };
		//Msg directory{ "Введите путь для сохранения файлов ($ - текущая папка): " };

	} // namespace input

	namespace error {

		Msg wrong_input{ "Некорректные данные." };
		//Msg no_file{ "Файл не существует." };
		//Msg no_directory{ "Папка не существует." };
		//Msg file_cant_exist{ "Файл с такой директорией не может существовать." };
		//Msg cant_write{ "Файл не может быть изменён." };
		//Msg cant_access{ "Не удалось получить доступ к файлу." };
		//Msg cant_create{ "Не удалось создать файл." };

	} // namespace error

}
// Message.h
// РПС
// Лабораторная работа № 2.
// Студент группы 434, Пшеничников Максим Юрьевич. 2024 год

#pragma once

#include <string>
#include <vector>

namespace msg {

	using Msg = const std::string;
	using MsgVector = const std::vector<std::string>;

	Msg file_already_exists{ "Файл уже существует." };
	Msg save_completed{ "Сохранение завершено." };
	Msg reading_completed{ "Чтение файла завершено." };
	Msg menu_header{ "Выберите пункт меню: " };

	MsgVector rewrite_options{
		"Перезаписать файл",
		"Ввести другой путь",
		"Отменить сохранение"
	};

	namespace title {

		const size_t size = 30; // title size

		constexpr Msg centerize(Msg& title) {
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
		Msg	input{ "Введите массив: " };
		Msg output{ centerize("Вывод") };
		Msg cleared{ "Массив очищен." };
		Msg sorted{ "Массив отсортирован" };
		Msg random{ centerize("Генерация случайных значений") };
		Msg input_choice{ centerize("Выбор метода ввода") };
		Msg file_input{ "Загрузка массива из файла" };
		Msg file_output{ "Сохранение массива в файл" };

	} // namespace title

	namespace option {

		Msg input{ "Ввести массив" };
		Msg exit{ "Выйти из программы" };
		Msg return_to_main{ "Вернуться в главное меню" };
		Msg manual_input{"Ручной ввод"};
		Msg generate_random{ "Генерация случайных значений" };
		Msg from_file{ "Чтение данных из файла" };
		Msg show{ "Показать массив" };
		Msg clear{ "Очистить массив" };
		Msg sort{ "Отсортировать массив" };
		Msg save{ "Сохранить массив в файл" };

	} // namespace option

	namespace input {

		Msg choice{ "Ваш выбор: " };
		Msg file_path{ "Введите путь к файлу: " };
		Msg random_count{ "Число случайных чисел: " };
		Msg random_min{ "Минимальное: " };
		Msg random_max{ "Максимальное: " };
		//Msg directory{ "Введите путь для сохранения файлов ($ - текущая папка): " };

	} // namespace input

	namespace error {

		Msg wrong_input{ "Некорректные данные." };
		Msg no_file{ "Файл не существует." };
		//Msg no_directory{ "Папка не существует." };
		Msg file_cant_exist{ "Файл с такой директорией не может существовать." };
		Msg cant_write{ "Файл не может быть изменён." };
		Msg cant_access{ "Не удалось получить доступ к файлу." };
		Msg cant_create{ "Не удалось создать файл." };

	} // namespace error

}
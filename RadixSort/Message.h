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

		Msg main{ centerize("������� ����") };
		Msg	add{ centerize("����������") };
		Msg show{ centerize("�����") };
		Msg save{ centerize("����������") };
		Msg dialogs{ centerize("�������") };

	} // namespace title

	namespace input {

		Msg choice{ "��� �����: " };
		//Msg file_path{ "������� ���� � �����: " };
		//Msg text{ "������� �����. ���� ������������ $." };
		//Msg directory{ "������� ���� ��� ���������� ������ ($ - ������� �����): " };

	} // namespace input

	namespace error {

		Msg wrong_input{ "������������ ������." };
		//Msg no_file{ "���� �� ����������." };
		//Msg no_directory{ "����� �� ����������." };
		//Msg file_cant_exist{ "���� � ����� ����������� �� ����� ������������." };
		//Msg cant_write{ "���� �� ����� ���� ������." };
		//Msg cant_access{ "�� ������� �������� ������ � �����." };
		//Msg cant_create{ "�� ������� ������� ����." };

	} // namespace error

}
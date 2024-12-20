// Message.h
// ���
// ������������ ������ � 2.
// ������� ������ 434, ����������� ������ �������. 2024 ���

#pragma once

#include <string>
#include <vector>

namespace msg {

	using Msg = const std::string;
	using MsgVector = const std::vector<std::string>;

	Msg file_already_exists{ "���� ��� ����������." };
	Msg save_completed{ "���������� ���������." };
	Msg reading_completed{ "������ ����� ���������." };
	Msg menu_header{ "�������� ����� ����: " };

	MsgVector rewrite_options{
		"������������ ����",
		"������ ������ ����",
		"�������� ����������"
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

		Msg main{ centerize("������� ����") };
		Msg	input{ "������� ������: " };
		Msg output{ centerize("�����") };
		Msg cleared{ "������ ������." };
		Msg sorted{ "������ ������������" };
		Msg random{ centerize("��������� ��������� ��������") };
		Msg input_choice{ centerize("����� ������ �����") };
		Msg file_input{ "�������� ������� �� �����" };
		Msg file_output{ "���������� ������� � ����" };

	} // namespace title

	namespace option {

		Msg input{ "������ ������" };
		Msg exit{ "����� �� ���������" };
		Msg return_to_main{ "��������� � ������� ����" };
		Msg manual_input{"������ ����"};
		Msg generate_random{ "��������� ��������� ��������" };
		Msg from_file{ "������ ������ �� �����" };
		Msg show{ "�������� ������" };
		Msg clear{ "�������� ������" };
		Msg sort{ "������������� ������" };
		Msg save{ "��������� ������ � ����" };

	} // namespace option

	namespace input {

		Msg choice{ "��� �����: " };
		Msg file_path{ "������� ���� � �����: " };
		Msg random_count{ "����� ��������� �����: " };
		Msg random_min{ "�����������: " };
		Msg random_max{ "������������: " };
		//Msg directory{ "������� ���� ��� ���������� ������ ($ - ������� �����): " };

	} // namespace input

	namespace error {

		Msg wrong_input{ "������������ ������." };
		Msg no_file{ "���� �� ����������." };
		//Msg no_directory{ "����� �� ����������." };
		Msg file_cant_exist{ "���� � ����� ����������� �� ����� ������������." };
		Msg cant_write{ "���� �� ����� ���� ������." };
		Msg cant_access{ "�� ������� �������� ������ � �����." };
		Msg cant_create{ "�� ������� ������� ����." };

	} // namespace error

}
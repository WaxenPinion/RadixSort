#include "ButtonLogic.hpp"

#include "Sort.h"
#include "Consoleio.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


static inline void showMsg(sf::Text& msg_text, const sf::String& msg, sf::Color color) {
	msg_text.setFillColor(color);
	msg_text.setString(msg);
}


static bool proccessResponse(const sf::Http::Response& response, sf::Text& msg) {

	cout << "status code: " << response.getStatus();
	cout << " body: " << response.getBody() << endl;

	switch (response.getStatus())
	{
	case sf::Http::Response::Ok:
		return true;
	case sf::Http::Response::ConnectionFailed:
		showMsg(msg, L"Не удалось подключиться к серверу", sf::Color::Red);
		break;
	case sf::Http::Response::NoContent:
		showMsg(msg, L"Массива c таким номером в БД нет", sf::Color::Red);
		break;
	case sf::Http::Response::InternalServerError:
		showMsg(msg, L"Проблемы с БД", sf::Color::Red);
		break;
	default:
		break;
	}

	return false;
}


sf::Http::Response sendGetRequest(sf::Http& http, const string& uri) {

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Get);
	request.setField("From", "me");
	request.setUri(uri);

	return http.sendRequest(request);
}


sf::Http::Response sendPostRequest(sf::Http& http, const string& body) {

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Post);
	request.setField("From", "me");
	request.setField("Content-Type", "text/plain");
	request.setBody(body);

	return http.sendRequest(request);
}


vector<sf::String> splitAllArrays(const string& response) {

	stringstream stream{ response };
	string tmp{};
	vector<sf::String> result{};

	while (getline(stream, tmp, '/')) {
		result.push_back(tmp);
	}

	return result;
}


sf::String sortStringArray(const sf::String& str) {

	stringstream stream{ str };
	vector<int> vec{};

	stream >> vec;
	radixSort<int>(vec);
	stream << vec;

	return stream.str();
}


static void showPage(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content,
	std::vector<Entry>& db_ids, int& current_page) {

	for (size_t i = 0; i < 10; ++i) {
		db_entries.at(i).setString("");
		db_ids.at(i).setString("");
	}

	size_t tmp = db_content.size() - current_page * 10;
	for (size_t i = 0; i < ((tmp < 10) ? tmp : 10); ++i) {
		db_entries.at(i).setString(db_content.at(i + current_page * 10));
		db_ids.at(i).setString(to_string(i + current_page * 10 + 1));
	}
}


void sortArray(Entry& entry, sf::Text& msg) {

	if (entry.getString().isEmpty() and entry.getString()[0] != ' ') {
		showMsg(msg, L"Массив пуст", sf::Color::Red);
		return;
	}

	showMsg(msg, L"Сортировка массива", sf::Color::Black);
	entry.setString(sortStringArray(entry.getString()));
	showMsg(msg, L"Массив отсортирован", sf::Color::Green);
}


void addArray(const Entry& entry, sf::Http& http, sf::Text& msg) {

	if (entry.getString().isEmpty() and entry.getString()[0] != ' ') {
		showMsg(msg, L"Массив пуст", sf::Color::Red);
		return;
	}

	showMsg(msg, L"Добавление массива в базу данных", sf::Color::Black);

	sf::Http::Response response = sendPostRequest(http, "add/" + entry.getString());

	if (proccessResponse(response, msg)) {
		showMsg(msg, L"Массив добавлен в БД", sf::Color::Green);
	}
}


void changeArray(const Entry& entry, const Entry& id, sf::Http& http, sf::Text& msg) {

	if (id.getString().isEmpty()) {
		showMsg(msg, L"Укажите номер массива", sf::Color::Red);
		return;
	}
	if (entry.getString().isEmpty() and entry.getString()[0] != ' ') {
		showMsg(msg, L"Массив пуст", sf::Color::Red);
		return;
	}

	showMsg(msg, L"Изменение массива в базе данных", sf::Color::Black);

	sf::Http::Response response = sendPostRequest(http,
		"change/" + id.getString() + "/" + entry.getString());

	if (proccessResponse(response, msg)) {
		showMsg(msg, L"Массив изменён", sf::Color::Green);
	}
}

void deleteArray(const Entry& id, sf::Http& http, sf::Text& msg) {

	if (id.getString().isEmpty()) {
		showMsg(msg, L"Укажите номер массива", sf::Color::Red);
		return;
	}

	showMsg(msg, L"Удаление массива из базы данных", sf::Color::Black);

	sf::Http::Response response = sendPostRequest(http,
		"delete/" + id.getString());

	if (proccessResponse(response, msg)) {
		showMsg(msg, L"Массив удалён", sf::Color::Green);
	}

}


void getArray(Entry& entry, const Entry& id, sf::Http& http, sf::Text& msg) {

	if (id.getString().isEmpty()) {
		showMsg(msg, L"Укажите номер массива", sf::Color::Red);
		return;
	}

	showMsg(msg, L"Извлечение массива из базы данных", sf::Color::Black);

	sf::Http::Response response = sendGetRequest(http, "/?index=" + id.getString());

	if (proccessResponse(response, msg)) {
		entry.setString(response.getBody());
		showMsg(msg, L"Массив извлечён", sf::Color::Green);
	}
}


void getAllArrays(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content, 
	std::vector<Entry>& db_ids, int& current_page, sf::Http& http, sf::Text& msg) {

	showMsg(msg, L"Извлечение всех массивов", sf::Color::Black);

	sf::Http::Response response = sendGetRequest(http, "/?all");

	if (proccessResponse(response, msg)) {
		
		current_page = 0;

		db_content = splitAllArrays(response.getBody());

		showPage(db_entries, db_content, db_ids, current_page);
		showMsg(msg, L"Массивы извлечены", sf::Color::Green);
	}
}


void changePage(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content,
	std::vector<Entry>& db_ids, int& current_page, int shift, sf::Text& msg) {

	if (db_content.size() <= 10 * (current_page + shift) or current_page + shift < 0) return;

	current_page += shift;
	showPage(db_entries, db_content, db_ids, current_page);
}

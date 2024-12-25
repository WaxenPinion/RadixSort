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

	cout << response.getStatus() << response.getBody() << endl;

	switch (response.getStatus())
	{
	case sf::Http::Response::Ok:
		return true;
	case sf::Http::Response::ConnectionFailed:
		showMsg(msg, L"Не удалось подключиться к серверу", sf::Color::Red);
		break;
	case sf::Http::Response::NoContent:
		showMsg(msg, L"Массива c таким номером в БД нет", sf::Color::Black);
		break;
	case sf::Http::Response::InternalServerError:
		showMsg(msg, L"Проблемы с БД", sf::Color::Red);
		break;
	default:
		break;
	}
	return false;
}


static sf::Http::Response sendGetRequest(sf::Http& http, 
	const string& uri) {

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Get);
	request.setField("From", "me");

	request.setUri(uri);

	return http.sendRequest(request);
}


sf::Http::Response sendPostRequest(sf::Http& http,
	const string& body) {

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Post);
	request.setField("From", "me");
	request.setField("Content-Type", "text/plain");
	request.setBody(body);

	return http.sendRequest(request);
}


static void showPage(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content,
	int& current_page) {

	for (auto& el : db_entries) el.setString("");

	size_t tmp = db_content.size() - current_page * 10;
	for (size_t i = 0; i < ((tmp < 10) ? tmp : 10); ++i) {
		cout << endl << i << endl;
		db_entries.at(i).setString(db_content.at(i + current_page * 10));
	}
}


void sortArray(Entry& entry, sf::Text& msg) {

	if (entry.getString().isEmpty() and entry.getString()[0] != ' ') {
		showMsg(msg, L"Массив пуст", sf::Color::Red);
		return;
	}

	stringstream stream{ entry.getString() };
	vector<int> vec{};

	stream >> vec;
	radixSort<int>(vec);
	stream << vec;

	entry.setString(stream.str());
	showMsg(msg, L"Массив отсортирован", sf::Color::Black);
}


void addArray(const Entry& entry, sf::Http& http, sf::Text& msg) {

	if (entry.getString().isEmpty() and entry.getString()[0] != ' ') {
		showMsg(msg, L"Массив пуст", sf::Color::Red);
		return;
	}

	sf::Http::Response response = sendPostRequest(http, "add/" + entry.getString());

	if (proccessResponse(response, msg)) {
		showMsg(msg, L"Массив добавлен в БД", sf::Color::Black);
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

	sf::Http::Response response = sendPostRequest(http,
		"change/" + id.getString() + "/" + entry.getString());

	if (proccessResponse(response, msg)) {
		showMsg(msg, L"Массив изменён", sf::Color::Black);
	}
}


void getArray(Entry& entry, const Entry& id, sf::Http& http, sf::Text& msg) {

	if (id.getString().isEmpty()) {
		showMsg(msg, L"Укажите номер массива", sf::Color::Red);
		return;
	}

	sf::Http::Response response = sendGetRequest(http, "/?index=" + id.getString());

	if (proccessResponse(response, msg)) {
		entry.setString(response.getBody());
		showMsg(msg, L"Массив извлечён", sf::Color::Black);
	}
}


void getAllArrays(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content, 
	int& current_page, sf::Http& http, sf::Text& msg) {

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Get);
	request.setField("From", "me");

	request.setUri("/?all");

	sf::Http::Response response = http.sendRequest(request);

	if (proccessResponse(response, msg)) {
		
		current_page = 0;
		db_content.clear();

		stringstream stream{ response.getBody() };
		string tmp{};

		while (getline(stream, tmp, '/')) {
			db_content.push_back(tmp);
			cout << tmp << endl;
		}
		//in.clear();
		showPage(db_entries, db_content, current_page);
		showMsg(msg, L"Массивы извлечены", sf::Color::Black);
	}
}


void changePage(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content,
	int& current_page, int shift, sf::Text& msg) {

	if (db_content.size() <= 10 * (current_page + shift) or current_page + shift < 0) return;
		//showMsg(msg, L"Укажите номер массива", sf::Color::Red);

	current_page += shift;
	showPage(db_entries, db_content, current_page);
}

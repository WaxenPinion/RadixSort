#pragma once

#include "Entry.hpp"

#include <SFML/Network.hpp>

#include <vector>

sf::Http::Response sendPostRequest(sf::Http& http, const std::string& body);

void sortArray(Entry& entry, sf::Text& msg);
void addArray(const Entry& entry, sf::Http& http, sf::Text& msg);
void changeArray(const Entry& entry, const Entry& id, sf::Http& http, sf::Text& msg);
void getArray(Entry& entry, const Entry& id, sf::Http& http, sf::Text& msg);

void getAllArrays(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content, 
	int& current_page, sf::Http& http, sf::Text& msg);
void changePage(std::vector<Entry>& db_entries, std::vector<sf::String>& db_content, 
	int& current_page, int shift, sf::Text& msg);

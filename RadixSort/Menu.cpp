// Menu.cpp

#include "Consoleio.h"
#include "Menu.h"

#include <iostream>
#include <string>
#include <vector>


MenuPtr OptionMenu::execute(std::vector<int>& data) {

	std::vector<size_t> active_options{};
	std::vector<std::string> option_names{};

	for (size_t i = 0; i < m_options.size(); ++i) {
		if (!m_options.at(i).condition or m_options.at(i).condition(data)) {
			active_options.push_back(i);
			option_names.push_back(m_options.at(i).name);
		}
	}
	output::showOptions(option_names);
	return m_options.at(active_options.at(input::getOption(active_options.size()))).ptr;
	
}


OptionMenu& OptionMenu::addOption(const std::string& name, MenuPtr next,
	bool(*predicate)(std::vector<int>&)) {
	
	m_options.push_back(Option(name, next, predicate));
	if (next) next->setNext(this);


	return *this;
}


void MenuController::start(MenuPtr first) {

	m_next = first;
	while (m_next) {
		m_next->showTitle();
		m_next = m_next->execute(m_data);
		std::cout << std::endl;
	}

}


Menu& Menu::setNext(Menu* next) {

	m_next = next;

	return *this;
}


void Menu::showTitle() const {
	std::cout << m_title << std::endl;
}


MenuPtr ProcessMenu::execute(std::vector<int>& data) {
	m_func(data);
	return m_next;
}


ProcessMenu& ProcessMenu::setFunction(void(*func)(std::vector<int>&)) {
	m_func = func;
	return *this;
}

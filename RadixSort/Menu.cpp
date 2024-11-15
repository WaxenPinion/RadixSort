#include "Menu.h"
#include "Consoleio.h"

//#include <string>
#include <iostream>


MenuPtr OptionMenu::execute(std::vector<int>& data) {

	//ShowTitle
	//std::cout << "Options" << std::endl;
	//ShowOptions
	//int i = 0; //GetInt()
	if (m_predicate and m_predicate(data)) {
		output::showOptions(m_title, m_options, m_constant);
		return m_ptrs.at(m_constant.at(input::getOption(m_constant.size())));
	}
	else {
		output::showOptions(m_title, m_options);
		return m_ptrs.at(input::getOption(m_options.size()));
	}
	
}


OptionMenu& OptionMenu::addOption(const std::string& name, MenuPtr next, bool constant) {
	
	m_options.push_back(name);
	m_ptrs.push_back(next);
	if (constant) m_constant.push_back(m_options.size() - 1);

	return *this;
}


OptionMenu& OptionMenu::setPredicate(bool(*predicate)(std::vector<int>&)) {

	m_predicate = predicate;

	return *this;
}


MenuPtr InputMenu::execute(std::vector<int>& data) {

	//ShowTitle
	int a = 0;
	std::cout << m_title << std::endl;

	//std::cin >> a;

	//change
	data.push_back(input::getInt("> "));

	return m_next;
}


MenuPtr ProcessMenu::execute(std::vector<int>& data) {

	for (int& el : data) {
		std::cout << el << ", ";
	}
	std::cout << std::endl;

	return m_next;
}


void MenuController::start(MenuPtr first) {
	//m_menus = menus;
	m_next = first;
	while (m_next) {
		m_next = m_next->execute(data);
	}

}


/*MenuController& MenuController::addMenu(MenuPtr menu) {

	m_menus.push_back(menu);
	
	return *this;
}*/


void Menu::setNext(std::shared_ptr<Menu> next) {

	m_next = next;

}


std::shared_ptr<Menu> Menu::end() {

	std::shared_ptr<Menu> ptr{};
	ptr.reset();
	return ptr;
}

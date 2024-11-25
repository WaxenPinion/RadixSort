#include "Menu.h"
#include "Consoleio.h"
#include "Utils.h"

//#include <string>
#include <iostream>


MenuPtr OptionMenu::execute(std::vector<int>& data) {

	//ShowTitle
	//std::cout << "Options" << std::endl;
	//ShowOptions
	//int i = 0; //GetInt()
	std::vector<size_t> active_options{};
	std::vector<std::string> option_names{};

	for (size_t i = 0; i < m_options.size(); ++i) {
		if (!m_options.at(i).condition or m_options.at(i).condition(data)) {
			active_options.push_back(i);
			option_names.push_back(m_options.at(i).name);
		}
	}
	output::showOptions(m_title, option_names);
	return m_options.at(active_options.at(input::getOption(active_options.size()))).ptr;

	/*for (size_t i = 0; i < m_ops.size(); ++i) {
		if (!m_conditions.at(i) or m_conditions.at(i)(data)) to_show.push_back(i);
	}
	output::showOptions(m_title, m_ops, to_show);
	return m_ptrs.at(to_show.at(input::getOption(to_show.size())));*/

	/*if (m_predicate and m_predicate(data)) {
		output::showOptions(m_title, m_options, m_constant);
		return m_ptrs.at(m_constant.at(input::getOption(m_constant.size())));
	}
	else {
		output::showOptions(m_title, m_options);
		return m_ptrs.at(input::getOption(m_options.size()));
	}*/
	
}


OptionMenu& OptionMenu::addOption(const std::string& name, MenuPtr next,
	bool(*predicate)(std::vector<int>&)) {
	
	//m_ops.push_back(name);
	//m_ptrs.push_back(next);
	//m_conditions.push_back(predicate);
	m_options.push_back(Option(name, next, predicate));
	if (next) next->setNext(this);
	//next->setNext(std::make_shared<OptionMenu>(*this));
	//if (constant) m_constant.push_back(m_options.size() - 1);

	return *this;
}


MenuPtr InputMenu::execute(std::vector<int>& data) {

	//ShowTitle
	int a = 0;
	std::cout << m_title << std::endl;

	//std::cin >> a;

	//change
	//data.push_back(input::getInt("> "));
	std::cin >> data;

	return m_next;
}


MenuPtr OutputMenu::execute(std::vector<int>& data) {

	output::showVector<int>(data, m_title);

	return m_next;
}


void MenuController::start(MenuPtr first) {

	m_next = first;
	while (m_next) {
		m_next = m_next->execute(m_data);
	}

}


/*MenuController& MenuController::addMenu(MenuPtr menu) {

	m_menus.push_back(menu);
	
	return *this;
}*/


Menu& Menu::setNext(Menu* next) {

	m_next = next;

	return *this;
}


/*Menu* Menu::end() {

	//std::shared_ptr<Menu> ptr{};
	//ptr.reset();
	//return ptr;
	return nullptr;
}*/

MenuPtr ClearMenu::execute(std::vector<int>& data) {
	data.clear();
	std::cout << m_title << std::endl;
	return m_next;
}

MenuPtr ProcessMenu::execute(std::vector<int>& data) {
	std::cout << m_title << std::endl;
	data = m_func(data);
	return m_next;
}

ProcessMenu& ProcessMenu::setFunction(std::vector<int>(*func)(std::vector<int>&)) {
	m_func = func;
	return *this;
}

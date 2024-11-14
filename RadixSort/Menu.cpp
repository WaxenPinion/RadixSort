#include "Menu.h"

//#include <string>

MenuPtr OptionMenu::Execute(std::vector<int>& vec) {

	//ShowTitle
	//ShowOptions
	int i = 0; //GetInt()
	return m_options.at(i).next;
}


OptionMenu& OptionMenu::AddOption(const std::string& name, MenuPtr next) {
	
	m_options.push_back(Option(name, next));

	return *this;
}


MenuPtr InputMenu::Execute(std::vector<int>& vec) {

	//ShowTitle

	return MenuPtr();
}

void MenuController::Start() {

	while (!m_stop) {
		m_next = m_next->Execute(vec);
	}

}

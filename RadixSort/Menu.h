#pragma once

//#include "Message.h"

#include <vector>
#include <memory>
#include <string>


class Menu {
public:

	Menu() = default;
	Menu(const std::string& title)
		: m_title{ title } {};
	virtual ~Menu() = default;

	virtual std::shared_ptr<Menu> execute(std::vector<int>& data) = 0;

	void setNext(std::shared_ptr<Menu> next);

	static std::shared_ptr<Menu> end();

protected:

	std::string m_title{ "" };
	std::shared_ptr<Menu> m_next{ end() };

};


using MenuPtr = std::shared_ptr<Menu>;
using MenuVector = std::vector<std::shared_ptr<Menu>>;


class OptionMenu : public Menu {

	/*struct Option {

		Option(const std::string& name_, MenuPtr next_)
			: name{ name_ }
			, next{ next_ } {};
		
		std::string name;
		MenuPtr next;
	};*/

public:

	OptionMenu() = default;
	OptionMenu(std::string title)
		: Menu(title) {};
	virtual ~OptionMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	OptionMenu& addOption(const std::string& name, MenuPtr next, bool constant = true);
	OptionMenu& setPredicate(bool(*predicate)(std::vector<int>&));
	//OptionMenu& AddOption(std::string name, )

private:
	
	std::vector<std::string> m_options;
	std::vector<MenuPtr> m_ptrs;
	std::vector<size_t> m_constant;
	
	// if true, only constant options will be displayed
	bool(*m_predicate)(std::vector<int>&) = nullptr;

};


class InputMenu : public Menu {
public:

	InputMenu() = default;
	InputMenu(std::string title)
		: Menu(title) {};
	virtual ~InputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	//InputMenu& setNext(MenuPtr next);

private:

	//int(*m_func)(const std::string&) = nullptr;
	//MenuPtr m_next;

};


class ProcessMenu : public Menu {
public:

	ProcessMenu() = default;
	ProcessMenu(std::string title)
		: Menu(title) {};
	virtual ~ProcessMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

};


class MenuController {
public:

	MenuController() = default;
	~MenuController() = default;

	void start(MenuPtr first);

	//MenuController& addMenu(MenuPtr menu);

private:

	MenuPtr m_next = Menu::end();
	//std::vector<MenuPtr> m_menus{};
	bool m_stop = false;

	//placeholder
	std::vector<int> data{};

};

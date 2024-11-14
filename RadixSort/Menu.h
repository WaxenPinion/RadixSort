#pragma once

#include "Message.h"

#include <vector>
#include <memory>
#include <string>


class Menu {
public:

	Menu() = default;
	Menu(std::string& title)
		: m_title{ title } {};
	virtual ~Menu() = default;

	virtual std::shared_ptr<Menu> Execute(std::vector<int>& vec) = 0;

private:

	std::string m_title;

};


using MenuPtr = std::shared_ptr<Menu>;


class OptionMenu : public Menu {

	struct Option {

		Option(const std::string& name_, MenuPtr next_)
			: name{ name_ }
			, next{ next_ } {};
		
		std::string name;
		MenuPtr next;
	};

public:

	OptionMenu() = default;
	OptionMenu(std::string title)
		: Menu(title) {};
	virtual ~OptionMenu() = default;

	virtual MenuPtr Execute(std::vector<int>& vec) override;

	OptionMenu& AddOption(const std::string& name, MenuPtr next);
	//OptionMenu& AddOption(std::string name, )

private:
	
	std::vector<Option> m_options;

};


class InputMenu : public Menu {
public:

	InputMenu() = default;
	InputMenu(std::string title, MenuPtr ret)
		: Menu(title)
		, m_ret{ ret } {};
	virtual ~InputMenu() = default;

	virtual MenuPtr Execute(std::vector<int>& vec) override;

private:

	MenuPtr m_ret;

};


class MenuController {
public:

	MenuController() = default;
	~MenuController() = default;

	void Start();

private:

	MenuPtr m_next;
	std::vector<MenuPtr> m_menus;
	bool m_stop = false;

	std::vector<int> vec;

};

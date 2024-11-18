#pragma once

//#include "Message.h"

#include <vector>
#include <memory>
#include <string>


class Menu {
public:

	//Menu() = default;
	Menu(const std::string& title)
		: m_title{ title } {};
	virtual ~Menu() = default;

	virtual std::shared_ptr<Menu> execute(std::vector<int>& data) = 0;

	Menu& setNext(std::shared_ptr<Menu> next);

	static std::shared_ptr<Menu> end();

protected:

	std::string m_title{ "" };
	std::shared_ptr<Menu> m_next{ end() };

};


using MenuPtr = std::shared_ptr<Menu>;
using MenuVector = std::vector<std::shared_ptr<Menu>>;


class OptionMenu : public Menu {

	struct Option {

		Option(const std::string& name_, MenuPtr ptr_, bool(*condition_)(std::vector<int>&))
			: name{ name_ }
			, ptr{ ptr_ }
			, condition{ condition_ } {};
		std::string name{};
		MenuPtr ptr{};
		bool(*condition)(std::vector<int>&) = nullptr;
	};

public:

	//OptionMenu() = default;
	OptionMenu(const std::string& title)
		: Menu(title) {};
	virtual ~OptionMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	OptionMenu& addOption(const std::string& name, MenuPtr next, 
		bool(*predicate)(std::vector<int>&) = nullptr);
	//OptionMenu& setPredicate(bool(*predicate)(std::vector<int>&));
	//OptionMenu& AddOption(std::string name, )

private:
	
	//std::vector<std::string> m_ops{};
	//std::vector<MenuPtr> m_ptrs{};
	//std::vector<size_t> m_constant{};
	//std::vector<bool(*)(std::vector<int>&)> m_conditions{};

	std::vector<Option> m_options{};
	
	// if true, only constant options will be displayed
	//bool(*m_predicate)(std::vector<int>&) = nullptr;

};


class InputMenu : public Menu {
public:

	//InputMenu() = default;
	InputMenu(const std::string& title)
		: Menu(title) {};
	virtual ~InputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	//InputMenu& setNext(MenuPtr next);

private:

	//int(*m_func)(const std::string&) = nullptr;
	//MenuPtr m_next;

};


class OutputMenu : public Menu {
public:

	//OutputMenu() = default;
	OutputMenu(const std::string& title)
		: Menu(title) {};
	virtual ~OutputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

};


class ClearMenu : public Menu {
public:

	ClearMenu(const std::string& title)
		: Menu(title) {};
	virtual ~ClearMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

};


class ProcessMenu : public Menu {
public:

	ProcessMenu(const std::string& title)
		: Menu(title) {};
	virtual ~ProcessMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	ProcessMenu& setFunction(std::vector<int>(*func)(std::vector<int>&));

private:
	
	std::vector<int>(*m_func)(std::vector<int>&) = nullptr;

};


class MenuController {
public:

	MenuController() = default;
	~MenuController() = default;

	void start(MenuPtr first);

	//MenuController& addMenu(MenuPtr menu);

private:

	MenuPtr m_next{ Menu::end() };
	//std::vector<MenuPtr> m_menus{};
	//bool m_stop = false;

	//placeholder
	std::vector<int> m_data{};

};

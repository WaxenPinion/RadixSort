#pragma once

//#include "Message.h"

#include <vector>
#include <memory>
#include <string>


class Menu {
public:

	//Menu() = default;
	Menu(const std::string& title)
		: m_title{ title } {}
	virtual ~Menu() = default;

	virtual Menu* execute(std::vector<int>& data) = 0;

	Menu& setNext(Menu* next);

	void showTitle();

	//static Menu* end();

protected:

	std::string m_title{ "" };
	Menu* m_next{ nullptr };

};


using MenuPtr = Menu*;
using MenuVector = std::vector<Menu*>;


class OptionMenu : public Menu {

	struct Option {

		Option(const std::string& name_, MenuPtr ptr_, bool(*condition_)(std::vector<int>&))
			: name{ name_ }
			, ptr{ ptr_ }
			, condition{ condition_ } {}
		std::string name{};
		MenuPtr ptr{};
		bool(*condition)(std::vector<int>&) = nullptr;
	};

public:

	//OptionMenu() = default;
	OptionMenu(const std::string& title)
		: Menu(title) {}
	virtual ~OptionMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	/// <summary>
	/// Adds option to the menu.
	/// Note: sets member m_next of "next" to self.  
	/// </summary>
	OptionMenu& addOption(const std::string& name, MenuPtr next = nullptr, 
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
		: Menu(title) {}
	virtual ~InputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	//InputMenu& setNext(MenuPtr next);

	//int(*m_func)(const std::string&) = nullptr;
	//MenuPtr m_next;

};


class OutputMenu : public Menu {
public:

	//OutputMenu() = default;
	OutputMenu(const std::string& title)
		: Menu(title) {}
	virtual ~OutputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

};


class ClearMenu : public Menu {
public:

	ClearMenu(const std::string& title)
		: Menu(title) {}
	virtual ~ClearMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

};


class ProcessMenu : public Menu {
public:

	ProcessMenu(const std::string& title,
		std::vector<int>(*func)(std::vector<int>&) = nullptr)
		: Menu(title)
		, m_func{func} {}
	virtual ~ProcessMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	ProcessMenu& setFunction(std::vector<int>(*func)(std::vector<int>&));

private:
	
	std::vector<int>(*m_func)(std::vector<int>&);

};


class FileInputMenu : public Menu {
public:

	FileInputMenu(const std::string& title)
		: Menu(title) {}
	virtual ~FileInputMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;
};


class MenuController {
public:

	MenuController() = default;
	~MenuController() = default;

	void start(MenuPtr first);

private:

	MenuPtr m_next = nullptr;

	//placeholder, or is it?
	std::vector<int> m_data{};
	//Buffer m_buffer{};

};

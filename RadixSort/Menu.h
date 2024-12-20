// Menu.h

#pragma once

#include <vector>
#include <string>


class Menu {
public:

	Menu(const std::string& title)
		: m_title{ title } {}
	virtual ~Menu() = default;

	virtual Menu* execute(std::vector<int>& data) = 0;

	Menu& setNext(Menu* next);

	//change
	void showTitle() const;

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

private:

	std::vector<Option> m_options{};

};


class ProcessMenu : public Menu {
public:

	ProcessMenu(const std::string& title,
		void(*func)(std::vector<int>&) = nullptr)
		: Menu(title)
		, m_func{func} {}
	virtual ~ProcessMenu() = default;

	virtual MenuPtr execute(std::vector<int>& data) override;

	ProcessMenu& setFunction(void(*func)(std::vector<int>&));

private:
	
	void(*m_func)(std::vector<int>&);

};


class MenuController {
public:

	MenuController() = default;
	~MenuController() = default;

	void start(MenuPtr first);

private:

	MenuPtr m_next = nullptr;

	std::vector<int> m_data{};

};

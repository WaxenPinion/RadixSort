#include "Button.hpp"
#include "Entry.hpp"
#include "Sort.h"
#include "Consoleio.h"
#include "ButtonLogic.hpp"
//#include "Utils.h"

#include <SFML/Graphics.hpp>
//#include "SFML/Network.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


int main() {

	const sf::Vector2i window_size{ 1000, 600 };
	const int margin = 50, text_height = 30, array_limit = 60, interval = 5;
	sf::Color light_grey{ 150, 150, 150 };

	sf::Font font{};
	if (!font.loadFromFile("assets/Roboto-Black.ttf")) return EXIT_FAILURE;
	sf::RenderWindow window{ sf::VideoMode(window_size.x, window_size.y), 
		L"Поразрядная сортировка" };
	UiCollection collection{};
	sf::Http http{ "localhost", 8000 };

	sf::RectangleShape background{ sf::Vector2f(window_size)};
	background.setFillColor(sf::Color(100, 100, 100));
	//sf::Texture texture{};
	//if (!texture.loadFromFile("assets/doS.png")) return EXIT_FAILURE;
	//background.setTexture(&texture);
	collection.add(background);
	 
	sf::Text default_text{ "", font };
	default_text.setFillColor(sf::Color::Black);

	sf::RectangleShape entry_bg{ sf::Vector2f(window_size.x - 4 * margin, text_height) };
	entry_bg.setOutlineColor(sf::Color::Black);

	Entry array_entry{entry_bg, default_text};
	array_entry.changeShape().setPosition(margin+text_height, margin);
	array_entry.setWhiteList("0123456789 ");
	array_entry.setLimit(array_limit);
	collection.add(array_entry);

	const sf::Vector2f scale = array_entry.getText().getScale();
	default_text.scale(scale);

	Entry index_entry{ array_entry };
	index_entry.changeShape().setSize(sf::Vector2f(margin + 2 * interval, text_height));
	index_entry.changeShape().move(sf::Vector2f(- index_entry.getWidth() - interval, 0));
	index_entry.setWhiteList("0123456789");
	index_entry.setLimit(5);
	collection.add(index_entry);

	vector<sf::Text> labels{};
	{
		sf::Text arr{ default_text }, db{ default_text }, number{ default_text },
			index{ default_text };

		arr.setString(L"Массив:");
		arr.setPosition(margin + text_height, text_height - interval);
		labels.push_back(arr);

		db.setString(L"Содержимое базы данных:");
		db.setPosition(margin + text_height, window_size.y / 3 - text_height);
		labels.push_back(db);

		number.setString(L"#");
		number.setPosition(margin / 2, window_size.y / 3 - text_height);
		labels.push_back(number);

		index.setString(L"#");
		index.setPosition(index_entry.getShape().getPosition());
		index.move(sf::Vector2f(index_entry.getWidth() / 2, -text_height + interval));
		labels.push_back(index);
	}
	collection.add(labels);
	
	sf::Text msg_text{ default_text };
	msg_text.setPosition(window_size.x / 2, 0);
	msg_text.setString("");
	collection.add(msg_text);
	
	vector<Entry> arrays_in_db{};
	vector<sf::Text> db_ids{};
	for (int i = 0; i < 10; ++i) {
		float pos_y = static_cast<float>(window_size.y / 3 + (text_height + interval) * (i + 1));

		arrays_in_db.push_back(Entry(entry_bg, default_text, false));
		arrays_in_db.back().changeShape().setPosition(margin+text_height, pos_y);

		db_ids.push_back(default_text);
		db_ids.back().setPosition(margin/2, pos_y);
		db_ids.back().setString(to_string(i+1));
	}
	collection.add(arrays_in_db);
	collection.add(db_ids);

	Button bt_template{
		sf::RectangleShape(sf::Vector2f(6 * text_height, text_height)),
		default_text
	};
	bt_template.changeShape().setFillColor(light_grey);
	bt_template.changeShape().setOutlineColor(sf::Color::Black);

	Button sort_bt{ bt_template };
	sort_bt.changeShape().setPosition(margin*2, margin+text_height+interval);
	sort_bt.setLabel(L"Отсортировать")
		.setFunction(Button::Func(bind(sortArray, ref(array_entry), ref(msg_text))));
	collection.add(sort_bt);
	
	Button add_bt{ bt_template };
	add_bt.changeShape().setPosition(margin * 6, margin + text_height + interval);
	add_bt.setLabel(L"Добавить запись")
		.setFunction(Button::Func(bind(addArray, ref(array_entry), ref(http), ref(msg_text))));
	collection.add(add_bt);

	Button change_bt{ bt_template };
	change_bt.changeShape().setPosition(
		window_size.x / 2 + interval, margin + text_height + interval);
	change_bt.setLabel(L"Изменить запись #")
		.setFunction(Button::Func(bind(changeArray, 
			ref(array_entry), ref(index_entry), ref(http), ref(msg_text))
		));
	collection.add(change_bt);

	Button get_bt{ bt_template };
	get_bt.changeShape().setPosition(change_bt.getShape().getPosition());
	get_bt.changeShape().move(sf::Vector2f(change_bt.getWidth() + interval, 0));
	get_bt.setLabel(L"Извлечь запись #")
		.setFunction(Button::Func(bind(getArray,
			ref(array_entry), ref(index_entry), ref(http), ref(msg_text))
		));
	collection.add(get_bt);

	int current_page = 0;
	vector<sf::String> db_content{};
	bt_template.changeShape().setSize(sf::Vector2f(8 * text_height, text_height));
	Button prev_page_bt{ bt_template }, next_page_bt{ bt_template }, get_all{ bt_template };

	prev_page_bt.changeShape().setPosition(margin + text_height, window_size.y / 3);
	prev_page_bt.setLabel(L"Предыдущая страница")
		.setFunction(Button::Func(bind(changePage,
			ref(arrays_in_db), ref(db_content), ref(current_page), -1, ref(msg_text))
		));
	collection.add(prev_page_bt);

	next_page_bt.changeShape().setPosition( margin + 9 * text_height + interval, window_size.y / 3);
	next_page_bt.setLabel(L"Следующая страница")
		.setFunction(Button::Func(bind(changePage,
			ref(arrays_in_db), ref(db_content), ref(current_page), 1, ref(msg_text))
		));
	collection.add(next_page_bt);

	get_all.changeShape().setPosition(margin + 17 * text_height + interval, window_size.y / 3);
	get_all.setLabel(L"Извлечь всё из БД")
		.setFunction(Button::Func(bind(getAllArrays,
			ref(arrays_in_db), ref(db_content), ref(current_page), ref(http), ref(msg_text))
		));
	collection.add(get_all);
	//prev_page_bt.changeShape().move(sf::Vector2f(change_bt.getWidth() + interval, 0));

	while (window.isOpen()) {

		sf::Event event{};
		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				break;
			default:
				break;
			}

			collection.processAll(event);
		}

		window.clear();

		window.draw(collection);

		//window.draw(text);
		/*if (view.getCenter().x < 100) to_left = false;
		else if (view.getCenter().x > 1000) to_left = true;
		if (to_left) view.move(-1, 0);
		else view.move(1, 0);
		window.setView(view);*/

		window.display();
	}
	
	/*sf::Http http{"localhost", 8000};

	sf::Http::Request request{};
	request.setMethod(sf::Http::Request::Post);
	//request.setUri("/");
	request.setField("From", "me");
	request.setField("Content-Type", "text/plain");
	request.setBody("param=value");

	sf::Http::Response response = http.sendRequest(request);

	cout << response.getBody() << endl;*/

	return EXIT_SUCCESS;
}
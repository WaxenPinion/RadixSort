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
#include <map>

using namespace std;


int main() {

	sf::Font font{};
	if (!font.loadFromFile("assets/Roboto-Black.ttf")) return EXIT_FAILURE;

	map<string, sf::Texture> textures{
		{"add", sf::Texture()},
		{"delete", sf::Texture()},
		{"export", sf::Texture()},
		{"import", sf::Texture()},
		{"sort", sf::Texture()},
		{"left", sf::Texture()},
		{"import_all", sf::Texture()},
		{"right", sf::Texture()}
	};
	for (auto& [key, value] : textures) {
		if (!value.loadFromFile("assets/icons/" + key + ".png")) return EXIT_FAILURE;
	}

	const sf::Vector2f window_size{ 1000, 600 };//pos of msg
	const float margin = 50,
		entry_height = 30,
		interval = 5,
		help_width = 350,

		entry_index_width = entry_height * 2 + interval,
		entry_array_width = window_size.x - 2 * margin - entry_index_width - 2 * interval
		- help_width,
		entry_index_pos_x = margin,
		entry_array_pos_x = margin + entry_index_width + interval,
		entry_cur_pos_y = margin,
		entry_db_pos_y = window_size.y / 3,
		offset_y = entry_height,
		msg_pos_y = entry_db_pos_y - 2.5F * offset_y,
		db_bts_pos_x = window_size.x / 2 - 1.5F * entry_height - interval,
		help_pos_x = entry_array_pos_x + entry_array_width + interval;
	 

	size_t array_limit = 60, index_limit = 5;
	sf::Color light_grey{ 150, 150, 150 };

	sf::RenderWindow window{
		sf::VideoMode(static_cast<int>(window_size.x), static_cast<int>(window_size.y)),
		L"Поразрядная сортировка"
	};
	sf::Http http{ "localhost", 8000 };

	UiCollection collection{};
	
	sf::RectangleShape background{ window_size };
	background.setFillColor(sf::Color(100, 100, 100));
	collection.add(background);

	sf::Text default_text{ "0", font };
	float text_scale = default_text.getLocalBounds().getSize().y / entry_height;
	default_text.scale({ text_scale, text_scale });
	default_text.setString("");
	default_text.setFillColor(sf::Color::Black);

	//map<string, sf::Text> help_text{};
	map<string, sf::Text> help_text{
		{"add", sf::Text(L"- Добавление массива в БД", font)},
		{"delete", sf::Text(L"- Удаление массива из БД", font)},
		{"export", sf::Text(L"- Изменение массив в БД", font)},
		{"import", sf::Text(L"- Извлечение массива из БД", font)},
		{"sort", sf::Text(L"- Сортировка массива", font)},
		{"left", sf::Text(L"- Перейти на прошлую страницу", font)},
		{"import_all", sf::Text(L"- Показать все массивы в БД", font)},
		{"right", sf::Text(L"- Перейти на следующую страницу", font)},
	};
	map<string, sf::RectangleShape> help_image{};
	int i = 0;
	for (auto& [key, value] : help_text) {
		float pos_y = margin + i++ * (interval + entry_height);

		help_image[key] = sf::RectangleShape({ entry_height, entry_height });
		help_image.at(key).setTexture(&textures.at(key));
		help_image.at(key).setPosition(help_pos_x, pos_y);
		collection.add(help_image.at(key));

		help_text.at(key).setPosition(help_pos_x + entry_height + interval, pos_y);
		help_text.at(key).scale({ text_scale, text_scale });
		help_text.at(key).setFillColor(sf::Color::Black);
		collection.add(help_text.at(key));

	}


	Entry array_entry{
		sf::RectangleShape({ entry_array_width, entry_height }),
		default_text
	},
	index_entry{
		sf::RectangleShape({entry_index_width, entry_height }),
		default_text
	};
	array_entry.changeShape().setOutlineColor(sf::Color::Black);
	index_entry.changeShape().setOutlineColor(sf::Color::Black);

	array_entry.changeShape().setPosition(entry_array_pos_x, entry_cur_pos_y);
	array_entry.setWhiteList("0123456789 ");
	array_entry.setLimit(array_limit);
	collection.add(array_entry);

	index_entry.changeShape().setPosition(entry_index_pos_x, entry_cur_pos_y);
	index_entry.setWhiteList("0123456789");
	index_entry.setLimit(index_limit);
	collection.add(index_entry);

	vector<sf::Text> labels{};
	{
		sf::Text label_cur_array{ default_text }, label_db_arrays{ default_text },
			label_cur_index{ default_text }, label_db_index{ default_text },
			label_msg{ default_text };

		label_cur_array.setString(L"Массив:");
		label_cur_array.setPosition(entry_array_pos_x, entry_cur_pos_y - offset_y);
		labels.push_back(label_cur_array);

		label_db_arrays.setString(L"Содержимое базы данных:");
		label_db_arrays.setPosition(entry_array_pos_x, entry_db_pos_y - offset_y);
		labels.push_back(label_db_arrays);

		label_cur_index.setString(L"#");
		label_cur_index.setPosition(entry_index_pos_x, entry_cur_pos_y - offset_y);
		labels.push_back(label_cur_index);

		label_db_index = label_cur_index;
		label_db_index.setPosition(entry_index_pos_x, entry_db_pos_y - offset_y);
		labels.push_back(label_db_index);

		label_msg.setString(L"Статус:");
		label_msg.setPosition(entry_index_pos_x, msg_pos_y);
		labels.push_back(label_msg);
	}
	collection.add(labels);

	sf::Text msg_text{ default_text };
	msg_text.setPosition(entry_array_pos_x + 2 * interval, msg_pos_y);
	msg_text.setString(L"Ожидание команд");
	collection.add(msg_text);

	vector<Entry> vec_db_arrays{}, vec_db_ids{};
	for (int i = 0; i < 10; ++i) {
		float pos_y = entry_db_pos_y + i * (interval + entry_height);

		vec_db_arrays.push_back(array_entry);
		vec_db_arrays.back().changeShape().setPosition(entry_array_pos_x, pos_y);
		vec_db_arrays.back().setActive(false);

		vec_db_ids.push_back(index_entry);
		vec_db_ids.back().changeShape().setPosition(entry_index_pos_x, pos_y);
		vec_db_ids.back().setActive(false);
	}
	collection.add(vec_db_arrays);
	collection.add(vec_db_ids);

	Button bt_template{
		sf::RectangleShape({ entry_height, entry_height })
	};
	sf::RectangleShape button_shape{ { entry_height, entry_height } };
	button_shape.setFillColor(light_grey);
	button_shape.setOutlineColor(sf::Color::Black);

	map<string, Button> buttons{};
	i = 0;
	for (auto& [key, value] : textures) {
		buttons[key] = Button(button_shape, value);
		buttons.at(key).changeShape().setPosition(
			entry_array_pos_x + i++ * (entry_height + interval),
			entry_cur_pos_y + offset_y + interval
		);
		collection.add(buttons.at(key));
	}

	int current_page = 0;
	vector<sf::String> db_content{};
	buttons.at("add").setFunction(bind(addArray, ref(array_entry), ref(http), ref(msg_text)));
	buttons.at("delete").setFunction(bind(deleteArray,
		ref(index_entry), ref(http), ref(msg_text)));
	buttons.at("export").setFunction(bind(changeArray,
		ref(array_entry), ref(index_entry), ref(http), ref(msg_text)));
	buttons.at("import").setFunction(bind(getArray,
		ref(array_entry), ref(index_entry), ref(http), ref(msg_text)));
	buttons.at("sort").setFunction(bind(sortArray, ref(array_entry), ref(msg_text)));
	buttons.at("left").setFunction(bind(changePage,
		ref(vec_db_arrays), ref(db_content), ref(vec_db_ids),
		ref(current_page), -1, ref(msg_text)));
	buttons.at("import_all").setFunction(bind(getAllArrays,
		ref(vec_db_arrays), ref(db_content), ref(vec_db_ids),
		ref(current_page), ref(http), ref(msg_text)));
	buttons.at("right").setFunction(bind(changePage,
		ref(vec_db_arrays), ref(db_content), ref(vec_db_ids),
		ref(current_page), 1, ref(msg_text)));

	vector<string> db_bts{ "left", "import_all", "right" };
	for (int i = 0; i < db_bts.size(); ++i) {
		buttons.at(db_bts.at(i)).changeShape().setPosition(
			db_bts_pos_x + i * (entry_height + interval),
			entry_db_pos_y - offset_y - interval
		);
	}

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

		window.display();
	}

	return EXIT_SUCCESS;
}

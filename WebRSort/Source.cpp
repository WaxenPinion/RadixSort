#include "Button.hpp"
#include "Entry.hpp"

#include <SFML/Graphics.hpp>
//#include "SFML/Network.hpp"

#include <iostream>

using namespace std;

int main() {

	sf::Font font{};
	if (!font.loadFromFile("assets/Roboto-Black.ttf")) return EXIT_FAILURE;

	sf::RenderWindow window{ sf::VideoMode(1000, 600), "SpeedConstant" };
	ItemCollection collection{};

	sf::Text text{ "Button", font };

	sf::RectangleShape rect{ sf::Vector2f(1000, 600) };
	//rect.setFillColor(sf::Color(100, 100, 100));
	//sf::Texture texture{};
	//if (!texture.loadFromFile("assets/doS.png")) return EXIT_FAILURE;
	//rect.setTexture(&texture);
	collection.add(rect);

	Button button{
		sf::RectangleShape(sf::Vector2f(100, 50)),
		text,
		[]() {cout << "pressed" << endl; } 
	};
	button.changeShape().setPosition(sf::Vector2f(50, 50));
	button.changeShape().setFillColor(sf::Color::Green);
	collection.add(button);
	
	Entry entry{ sf::RectangleShape(sf::Vector2f(150, 50)), font };
	entry.changeShape().setFillColor(sf::Color::Blue);
	collection.add(entry);

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

		/*for (const auto element : to_draw) {
			window.draw(*element);
		}*/
		//window.setView(window.getDefaultView());
		//window.draw(bt);
		//window.draw(field);

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
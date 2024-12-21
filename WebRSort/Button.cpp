#include "Button.hpp"

#include <iostream>

Button::Button(const sf::RectangleShape& shape, const sf::Text& text, void(*func)())
	: Interactable(shape)
	, m_text{ text }
	, m_func{ func } {
	centerizeText();
}


void Button::process(const sf::Event& event) {
	/*if (event.type == sf::Event::MouseButtonPressed) {
		switch (mode_)
		{
		case Button::Left:
			if (!event.mouseButton.button and checkMousePos(event.mouseButton)) func_();
			break;
		case Button::Right:
			if (event.mouseButton.button and checkMousePos(event.mouseButton)) func_();
			break;
		case Button::Both:
			if (checkMousePos(event.mouseButton)) func_();
			break;
		default:
			break;
		}

	}*/
	if (event.type == sf::Event::MouseButtonPressed and checkMouseButton(event.mouseButton)
			and isHovered(event.mouseButton) and m_func)
		m_func();
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Interactable::draw(target, states);

	states.transform.combine(getShape().getTransform());
	target.draw(m_text, states);

}


void Button::centerizeText() {
	
	sf::Vector2f pos{};

	pos.x = (getWidth() - m_text.getLocalBounds().width) / 2;
	pos.y = (getHeight() - m_text.getLocalBounds().height) / 2 - 10; // why 10? Just because
	
	m_text.setPosition(pos);

	//std::cout << getWidth() << " " << getHeight() << std::endl;
	//std::cout << text_.getLocalBounds().width << " " << text_.getLocalBounds().height << std::endl;
	//std::cout << pos.x << " " << pos.y << std::endl;

}

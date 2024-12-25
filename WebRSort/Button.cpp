#include "Button.hpp"

#include <iostream>

Button::Button(const sf::RectangleShape& shape, const sf::Text& text)
	: Interactable(shape)
	, m_text{ text } {

	if (m_text.getString().isEmpty()) m_text.setString("0");
	float factor = getHeight() / m_text.getGlobalBounds().height / 2;
	m_text.scale(factor, factor);
	m_text.setString(text.getString());

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
		and isHovered(event.mouseButton)) {
		setFocus(true);
		m_func();
	}
	else setFocus(false);
}

Button& Button::setLabel(const sf::String& label){
	m_text.setString(label);
	centerizeText();
	return *this;
}

Button& Button::setFunction(const Func& func) {
	m_func = func;
	return *this;
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Interactable::draw(target, states);

	states.transform.combine(getShape().getTransform());
	target.draw(m_text, states);

}


void Button::centerizeText() {
	
	sf::Vector2f pos{};

	pos.x = (getWidth() - m_text.getLocalBounds().width*m_text.getScale().x) / 2;
	//std::cout << getWidth() << std::endl;
	//std::cout << m_text.getLocalBounds().width * m_text.getScale().x << std::endl;
	//pos.y = (getHeight() - m_text.getLocalBounds().height) / 2 - 10; // why 10? Just because
	
	m_text.setPosition(pos);

	//std::cout << getWidth() << " " << getHeight() << std::endl;
	//std::cout << text_.getLocalBounds().width << " " << text_.getLocalBounds().height << std::endl;
	//std::cout << pos.x << " " << pos.y << std::endl;

}

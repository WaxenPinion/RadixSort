#include "Entry.hpp"

#include <iostream>

Entry::Entry(const sf::RectangleShape& shape, const sf::Text& text, bool active)
	: Interactable(shape)
	, m_text{ text }
	, m_str{ text.getString() }
	, m_active{ active } {

	if (m_text.getString().isEmpty()) m_text.setString("0");
	float factor = getHeight() / m_text.getGlobalBounds().height / 2;
	m_text.scale(factor, factor);
	m_text.setString(m_str);

}


void Entry::process(const sf::Event& event) {

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (isHovered(event.mouseButton)) setFocus(true);
		else setFocus(false);
		break;
	case sf::Event::TextEntered:
		if (!isFocused() or !m_active) break;
		//std::cout << event.text.unicode << std::endl;

		if (event.text.unicode == '\b' and !m_str.isEmpty()) m_str.erase(m_str.getSize() - 1);
		else if (m_str.getSize() >= m_limit and m_limit);
		else if (event.text.unicode == 13) m_str += '\n';
		else if (m_whitelist.isEmpty() or 
				m_whitelist.find(event.text.unicode) != sf::String::InvalidPos)
			m_str += event.text.unicode;

		m_text.setString(m_str);
		{
			size_t i = 1;
			while (getWidth() - m_text.getGlobalBounds().width < 0) {
				m_text.setString(m_str.substring(i));
				i++;
			}
		}
		//float delta = -(getWidth() - m_text.getGlobalBounds().width);
		//if (delta) m_str.substring()
		break;
	default:
		break;
	}
}

Entry& Entry::setWhiteList(const sf::String& whitelist) {
	m_whitelist = whitelist;
	return *this;
}

Entry& Entry::setText(const sf::Text& text) {
	m_text = text;
	m_str = text.getString();
	return *this;
}

const sf::Text& Entry::getText() const {
	return m_text;
}

Entry& Entry::setString(const sf::String& str) {
	m_str = str;
	m_text.setString(str);
	return *this;
}

const sf::String& Entry::getString() const {
	return m_str;
}

Entry& Entry::setLimit(size_t limit) {
	m_limit = limit;
	return *this;
}


void Entry::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Interactable::draw(target, states);
	states.transform.combine(getShape().getTransform());
	target.draw(m_text, states);

	//sf::View view{target.getDefaultView()};
	//sf::Vector2f size{ view.getSize() };
	//view.reset(sf::FloatRect(-sf::Vector2f(0, 0), sf::Vector2f(400, 300)));
	//std::cout << getPosition().x << " " << getPosition().y << std::endl;
	//view.setRotation(90);
	//view.setSize(getSize());
	//view.getSize() / getSize();
	//sf::Vector2f size{ getSize().x / view.getSize().x, getSize().y / view.getSize().y };
	
	//std::cout << view.getSize().x << " " << view.getSize().y << std::endl;
	//view.setViewport(sf::FloatRect(sf::Vector2f(0, 0), size));
	//view.setSize(getSize());
	//target.setView(view);
	
	//float delta = getWidth() - m_text.getGlobalBounds().width;
	//states.transform.translate(0, -getHeight()/2);
	//std::cout << m_text.getLocalBounds().width << std::endl;

	//if (delta < 0) states.transform.translate(delta, -10);

	//target.setView(target.getDefaultView());

}

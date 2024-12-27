#include "Button.hpp"

#include <iostream>

Button::Button()
	: Interactable(sf::RectangleShape())
	, m_text{ sf::Text() }
	, m_texture{ sf::RectangleShape() } {}

Button::Button(const sf::RectangleShape& shape, const sf::Text& text)
	: Interactable(shape)
	, m_text{ text }
	, m_texture{ sf::RectangleShape() } {

	if (m_text.getString().isEmpty()) m_text.setString("0");
	float factor = getHeight() / m_text.getGlobalBounds().height / 2;
	m_text.scale(factor, factor);
	m_text.setString(text.getString());

	centerizeText();
}

Button::Button(const sf::RectangleShape& shape, const sf::Texture& texture)
	: Interactable(shape)
	, m_texture{ shape }
	, m_text{ sf::Text() } {
	m_texture.setTexture(&texture);
}


void Button::process(const sf::Event& event) {
	
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

Button& Button::setTexture(const sf::Texture& texture) {
	m_texture.setTexture(&texture);
	m_texture.setSize(getShape().getSize());
	return *this;
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Interactable::draw(target, states);

	states.transform.combine(getShape().getTransform());
	target.draw(m_text, states);
	target.draw(m_texture, states);

}


void Button::centerizeText() {
	
	sf::Vector2f pos{};
	pos.x = (getWidth() - m_text.getLocalBounds().width*m_text.getScale().x) / 2;
	m_text.setPosition(pos);
}

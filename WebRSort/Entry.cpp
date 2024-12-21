#include "Entry.hpp"

Entry::Entry(const sf::RectangleShape& shape, const sf::Font& font)
	: Interactable(shape)
	, m_text{ sf::String(), font } {}


void Entry::process(const sf::Event& event) {

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (isHovered(event.mouseButton)) setFocus(true);
		else setFocus(false);
		break;
	case sf::Event::TextEntered:
		if (!isFocused()) break;
		if (event.text.unicode != '\b') m_str += event.text.unicode;
		else if (!m_str.isEmpty()) m_str.erase(m_str.getSize() - 1);
		m_text.setString(m_str);
		break;
	default:
		break;
	}
}


void Entry::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Interactable::draw(target, states);

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

	states.transform.combine(getShape().getTransform());
	float delta = getWidth() - m_text.getGlobalBounds().width;
	if (delta < 0) states.transform.translate(delta, 0);
	target.draw(m_text, states);

	//target.setView(target.getDefaultView());

}

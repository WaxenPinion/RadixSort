#include "Interactable.hpp"


void Interactable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//states.transform.combine(getTransform());
	target.draw(m_shape, states);
}


bool Interactable::isHovered(sf::Event::MouseButtonEvent postion) const{

	sf::Vector2f vec_pos{};
	vec_pos.x = static_cast<float>(postion.x);
	vec_pos.y = static_cast<float>(postion.y);

	return m_shape.getGlobalBounds().contains(vec_pos);
}

bool Interactable::isFocused() {
	return m_focused;
}

void Interactable::setFocus(bool state) {
	m_focused = state;
}


bool Interactable::checkMouseButton(sf::Event::MouseButtonEvent event_data) const{
	return m_mode == Both or m_mode == event_data.button;
}


float Interactable::getWidth() const {
	return m_shape.getLocalBounds().width;
}


float Interactable::getHeight() const {
	return m_shape.getLocalBounds().height;
}


void Interactable::setShape(const sf::RectangleShape& shape) {
	m_shape = shape;
}

const sf::RectangleShape& Interactable::getShape() const {
	return m_shape;
}

sf::RectangleShape& Interactable::changeShape() {
	return m_shape;
}

void Interactable::setMode(Mode mode) {
	m_mode = mode;
}

ItemCollection& ItemCollection::add(const sf::Drawable& drawable) {
	m_drawables.push_back(&drawable);
	return *this;
}

ItemCollection& ItemCollection::add(Interactable& interactable) {
	m_drawables.push_back(&interactable);
	m_interactables.push_back(&interactable);
	return *this;
}

void ItemCollection::processAll(const sf::Event& event) {
	for (Interactable* element : m_interactables) {
		element->process(event);
	}
}

void ItemCollection::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const sf::Drawable* element : m_drawables) {
		target.draw(*element, states);
	}
}

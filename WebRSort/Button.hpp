#pragma once

#include "Interactable.hpp"

#include <functional>


class Button : public Interactable {
public:
	using Func = std::function<void()>;

	Button();
	Button(const sf::RectangleShape& shape, const sf::Text& text = sf::Text());
	Button(const sf::RectangleShape& shape, const sf::Texture& texture);
	virtual ~Button() = default;

	virtual void process(const sf::Event& event) override;

	Button& setLabel(const sf::String& label);
	Button& setFunction(const Func& func);
	Button& setTexture(const sf::Texture& texture);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void centerizeText();

private:

	sf::Text m_text;
	Func m_func{};
	sf::RectangleShape m_texture;

};


/*template <typename T>
class ExButton : public Interactable {
public:

	ExButton(const sf::RectangleShape& shape,
		T& ref,
		const sf::Text& text = sf::Text(),
		void(*func)(T&) = nullptr)
		: Interactable(shape)
		, m_ref{ ref }
		, m_text{ text }
		, m_func{ func } {
		centerizeText();
	}
	virtual ~ExButton() = default;

	virtual void process(const sf::Event& event) override {
		if (event.type == sf::Event::MouseButtonPressed and checkMouseButton(event.mouseButton)
			and isHovered(event.mouseButton) and m_func)
			m_func(m_ref);
	}

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		Interactable::draw(target, states);

		states.transform.combine(getShape().getTransform());
		target.draw(m_text, states);
	}

	void centerizeText() {
		sf::Vector2f pos{};

		pos.x = (getWidth() - m_text.getLocalBounds().width) / 2;
		pos.y = (getHeight() - m_text.getLocalBounds().height) / 2 - 10; // why 10? Just because

		m_text.setPosition(pos);
	}

private:

	sf::Text m_text;
	void(*m_func)(T&);
	T& m_ref;

};*/

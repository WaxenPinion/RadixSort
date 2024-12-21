#pragma once

#include "Interactable.hpp"


class Button : public Interactable {
public:

	Button(const sf::RectangleShape& shape,
		const sf::Text& text = sf::Text(), 
		void(*func)() = nullptr);
	virtual ~Button() = default;

	virtual void process(const sf::Event& event) override;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void centerizeText();

private:

	sf::Text m_text;
	void(*m_func)();

};

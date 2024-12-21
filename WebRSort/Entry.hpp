#pragma once

#include "Interactable.hpp"


class Entry : public Interactable {
public:

	Entry(const sf::RectangleShape& shape, const sf::Font& font);
	Entry() = default;
	virtual ~Entry() = default;

	virtual void process(const sf::Event& event) override;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::String m_str{};
	sf::Text m_text{};

};

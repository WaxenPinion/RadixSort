#pragma once

#include "Interactable.hpp"


class Entry : public Interactable {
public:

	Entry(const sf::RectangleShape& shape, const sf::Text& text, bool active = true);
	Entry() = default;
	virtual ~Entry() = default;

	virtual void process(const sf::Event& event) override;

	Entry& setWhiteList(const sf::String& whitelist);

	Entry& setText(const sf::Text& text);
	const sf::Text& getText() const;

	Entry& setString(const sf::String& str);
	const sf::String& getString() const;

	Entry& setLimit(size_t limit);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::String m_str{};
	sf::String m_whitelist{};
	sf::Text m_text;
	bool m_active;
	size_t m_limit = 0;

};

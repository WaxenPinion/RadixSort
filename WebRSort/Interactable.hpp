#pragma once

#include <SFML/Graphics.hpp>

//#define SET_SHAPE(setter, arg_type) void setter(arg_type arg) { m_shape.setter(arg); }
//#define GET_SHAPE(getter, ret_type) ret_type getter() const { return shape_.getter(); }
#include <vector>
#include <map>

class Interactable : public sf::Drawable {
public:

	enum Mode {
		Left,
		Right,
		Both
	};

	Interactable(const sf::RectangleShape& shape)
		: m_shape{ shape } {}
	virtual ~Interactable() = default;

	virtual void process(const sf::Event& event) = 0;

	void setShape(const sf::RectangleShape& shape);
	const sf::RectangleShape& getShape() const;
	sf::RectangleShape& changeShape();

	void setMode(Mode mode);

	bool isHovered(sf::Event::MouseButtonEvent postion) const;

	bool isFocused();
	void setFocus(bool state);

	float getWidth() const;
	float getHeight() const;

	//SET_SHAPE(setPosition, const sf::Vector2f&)
	//SET_SHAPE(setScale, const sf::Vector2f&)
	
	//GET_SHAPE(getScale, sf::Vector2f)
	//GET_SHAPE(getTransform, sf::Transform)
	//GET_SHAPE(getPosition, sf::Vector2f)
	//GET_SHAPE(getSize, sf::Vector2f)

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool checkMouseButton(sf::Event::MouseButtonEvent event_data) const;

private:

	sf::RectangleShape m_shape;
	Mode m_mode{ Both };
	bool m_focused = false;

};


class UiCollection : public sf::Drawable {
public:

	UiCollection() = default;
	~UiCollection() = default;

	UiCollection& add(const sf::Drawable& drawable);
	UiCollection& add(Interactable& drawable);

	template <typename T>
	UiCollection& add(std::vector<T>& vec) {
		for (auto& element : vec) {
			add(element);
		}
		return *this;
	}

	template <typename T>
	UiCollection& add(std::map<std::string, T> m) {
		for (auto& [_key, value] : m) {
			add(value);
		}
		return *this;
	}

	void processAll(const sf::Event& event);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	std::vector<const sf::Drawable*> m_drawables{};
	std::vector<Interactable*> m_interactables{};

};

//#undef SET_SHAPE
//#undef GET_SHAPE

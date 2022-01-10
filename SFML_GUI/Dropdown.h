#pragma once

#include "Entity.h"

class Dropdown : public Entity
{
public:
	Dropdown();
	virtual ~Dropdown();

	void update(const sf::Vector2f& mousePos, sf::Event& event);
	void load_data() override;

	const int getActiveElement();
	sf::VideoMode setActiveElement();

private:
	std::vector<sf::VideoMode> modes;
	std::vector<sf::RectangleShape> elements;
	std::vector<sf::Color> backgrounds;
	std::vector<sf::Text> options;
	std::vector<sf::Text> active_text;
	std::vector<std::string> list;
	int active_element;
	bool show_list;

	void make_a_list();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};


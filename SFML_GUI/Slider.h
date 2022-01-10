#pragma once

#include "Entity.h"

class Slider : public Entity
{
public:
	Slider();
	virtual ~Slider();

	void update(const sf::Vector2f& mousePos, sf::Event& event);
	void load_data() override;

	const bool getValue(unsigned short int number);

private:
	std::vector<sf::RectangleShape> current_values;
	std::vector<float> m_values;
	std::vector<std::string> m_names;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};


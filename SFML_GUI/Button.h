#pragma once

#include "Entity.h"

class Button : public Entity
{
public:
	Button();
	virtual ~Button();

	void update(const sf::Vector2f& mousePos, sf::Event& event);
	void load_data() override;

	const bool getClicked(unsigned short int number);

private:
	std::vector<bool> m_clickeds;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};
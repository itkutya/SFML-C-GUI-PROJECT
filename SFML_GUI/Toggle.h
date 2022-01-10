#pragma once

#include "Entity.h"

class Toggle : public Entity
{
public:
	Toggle();
	virtual ~Toggle();

	void update(const sf::Vector2f& mousePos, sf::Event& event);
	void load_data() override;

	const bool getState(unsigned short int number);

private:
	std::vector<unsigned short int> m_states;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};
#pragma once

#include "Entity.h"

class Image : public Entity
{
public:
	Image();
	virtual ~Image();

	void update(const sf::Vector2f& mousePos, sf::Event& event);
	void load_data() override;

private:
	sf::Texture* texture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};


#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		states.texture = &this->m_textures[i];
		target.draw(this->m_shapes[i], states);
		if (this->m_texts[i].getString() != "")
		{
			target.draw(this->m_texts[i], states);
		}
	}
}
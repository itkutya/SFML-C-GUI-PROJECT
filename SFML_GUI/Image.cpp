#include "pch.h"

#include "Image.h"


Image::Image()
{
	this->load_data();
}

Image::~Image()
{
	delete[] this->texture;
}

void Image::update(const sf::Vector2f& mousePos, sf::Event& event)
{

}

void Image::load_data()
{
	this->m_count = 0;

	std::fstream file("resources/gui.txt");
	if (!file.good())
	{
		std::ofstream outfile("resources/gui.txt");
		outfile << "Reqierd data about entities are missing!";
		outfile.close();
		throw std::runtime_error("Restart requierd!");
	}
	file.close();

	std::ifstream data;
	data.open("resources/gui.txt");
	if (data.is_open())
	{
		std::string type = "";
		std::string path = "";
		sf::IntRect area;
		sf::Vector2f size;
		sf::Vector2f position;

		while (data >> type)
		{
			if (type == "IMAGE")
			{
				this->m_count++;

				this->m_shapes.push_back(sf::RectangleShape());

				data >> path >> area.left >> area.top >> area.width >> area.height >> size.x >> size.y >> position.x >> position.y;

				this->m_shapes[this->m_count - 1].setSize(size);
				this->m_shapes[this->m_count - 1].setPosition(position);
				this->m_shapes[this->m_count - 1].setOutlineThickness(2.f);

				this->texture = new sf::Texture[this->m_count];

				this->texture[this->m_count - 1].loadFromFile(path, area);
				this->m_shapes[this->m_count - 1].setTexture(&this->texture[this->m_count - 1]);
			}
		}
	}
	else
	{
		throw std::runtime_error("Cannot open data file.");
	}
	data.close();
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		states.texture = &this->texture[i];
		target.draw(this->m_shapes[i], states);
	}
}

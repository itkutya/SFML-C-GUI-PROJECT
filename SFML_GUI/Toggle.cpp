#include "pch.h"

#include "Toggle.h"

Toggle::Toggle()
{
	this->load_data();

	//Toggle
	this->m_pressed = false;

	//Text
	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		std::string l = this->m_texts[i].getString();
		std::size_t length = l.length();

		if (this->m_texts[i].getString() != "")
		{
			if (!this->m_font.loadFromFile("resources/sansation.ttf"))
			{
				throw std::runtime_error("Failed to find font!");
			}

			this->m_texts[i].setFont(this->m_font);
			this->m_texts[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));

			this->m_texts[i].setPosition(this->m_shapes[i].getPosition().x + (this->m_shapes[i].getGlobalBounds().width / 2.f) - this->m_texts[i].getGlobalBounds().width - this->m_shapes[i].getGlobalBounds().width,
										this->m_shapes[i].getPosition().y + (this->m_shapes[i].getGlobalBounds().height / 2.f) - this->m_texts[i].getGlobalBounds().height / 2.f - 5.f);
		}
	}
}

Toggle::~Toggle()
{

}

void Toggle::update(const sf::Vector2f& mousePos, sf::Event& event)
{
	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		if (this->m_shapes[i].getGlobalBounds().contains(mousePos))
		{
			if (event.type == sf::Event::MouseButtonPressed && this->m_states[i] == 0 && !this->m_pressed)
			{
				this->m_states[i] = 1;
				this->m_pressed = true;
			}
			else if (event.type == sf::Event::MouseButtonPressed && this->m_states[i] == 1 && !this->m_pressed)
			{
				this->m_states[i] = 0;
				this->m_pressed = true;
			}
		}

		if (this->m_states[i] == 0)
		{
			this->m_shapes[i].setFillColor(this->m_backgrounds[i]);
		}
		else if (this->m_states[i] == 1)
		{
			this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a));
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		this->m_pressed = false;
	}
}

void Toggle::load_data()
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
		std::string string = "";
		unsigned short int state = 0;
		sf::Vector2f size;
		sf::Vector2f position;
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;
		int t_r = 0;
		int t_g = 0;
		int t_b = 0;
		int t_a = 0;

		while (data >> type)
		{
			if (type == "TOGGLE")
			{
				this->m_count++;

				this->m_shapes.push_back(sf::RectangleShape());
				this->m_backgrounds.push_back(sf::Color());
				this->m_texts.push_back(sf::Text());
				this->m_states.push_back(0);

				data >> string >> state >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

				if (string == "-")
				{
					this->m_texts[this->m_count - 1].setString("");
				}
				else
				{
					this->m_texts[this->m_count - 1].setString(string);
				}
				this->m_states[this->m_count - 1] = state;
				this->m_shapes[this->m_count - 1].setSize(size);
				this->m_shapes[this->m_count - 1].setPosition(position);
				this->m_shapes[this->m_count - 1].setFillColor(sf::Color(r, g, b, a));
				this->m_shapes[this->m_count - 1].setOutlineThickness(5.f);
				this->m_shapes[this->m_count - 1].setOutlineColor(sf::Color(255, 255, 255, a));
				this->m_backgrounds[this->m_count - 1] = sf::Color(r, g, b, a);
				this->m_texts[this->m_count - 1].setFillColor(sf::Color(t_r, t_g, t_b, t_a));
			}
		}
	}
	else
	{
		throw std::runtime_error("Cannot open data file.");
	}
	data.close();
}

const bool Toggle::getState(unsigned short int number)
{
	return this->m_states[number];
}

void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		//states.texture = &this->m_textures[i];
		target.draw(this->m_shapes[i], states);
		if (this->m_texts[i].getString() != "")
		{
			target.draw(this->m_texts[i], states);
		}
	}
}
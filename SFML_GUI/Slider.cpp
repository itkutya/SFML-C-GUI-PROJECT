#include "pch.h"

#include "Slider.h"

Slider::Slider()
{
	this->load_data();

	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		//Slider
		this->current_values[i].setSize(sf::Vector2f(this->m_shapes[i].getSize().x * m_values[i], this->m_shapes[i].getSize().y));
		this->current_values[i].setPosition(this->m_shapes[i].getPosition());
		this->current_values[i].setFillColor(sf::Color(this->m_backgrounds[i].r / sf::Uint8(2.f), this->m_backgrounds[i].g / sf::Uint8(2.f), this->m_backgrounds[i].b / sf::Uint8(2.f), this->m_backgrounds[i].a));

		//Text
		std::string l = this->m_texts[i].getString();
		std::size_t  length = l.length();

		this->m_names[i] = this->m_texts[i].getString();

		if (this->m_texts[i].getString() != "")
		{
			if (!this->m_font.loadFromFile("resources/sansation.ttf"))
			{
				throw std::runtime_error("Failed to find font!");
			}

			this->m_texts[i].setFont(this->m_font);
			this->m_texts[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
			this->m_texts[i].setPosition(this->m_shapes[i].getPosition().x + (this->m_shapes[i].getGlobalBounds().width / 2.f) - this->m_texts[i].getGlobalBounds().width / 2.f - 10.f,
										this->m_shapes[i].getPosition().y + (this->m_shapes[i].getGlobalBounds().height / 2.f) - this->m_texts[i].getGlobalBounds().height / 2.f - 50.f);
		}
	}
}

Slider::~Slider()
{

}

void Slider::update(const sf::Vector2f& mousePos, sf::Event& event)
{
	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		if (this->m_shapes[i].getGlobalBounds().contains(mousePos))
		{
			this->m_shapes[i].setFillColor(this->m_backgrounds[i]);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b, this->m_backgrounds[i].a));
				this->m_values[i] -= 0.01f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b, this->m_backgrounds[i].a));
				this->m_values[i] += 0.01f;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b, this->m_backgrounds[i].a));
				this->m_values[i] = ((this->m_shapes[i].getPosition().x - mousePos.x) / this->m_shapes[i].getGlobalBounds().width) * -1;
			}
		}
		else
		{
			this->m_shapes[i].setFillColor(this->m_backgrounds[i]);
		}
		
		if (this->m_values[i] == 0.0f)
		{
			this->m_texts[i].setFillColor(sf::Color(this->m_texts[i].getFillColor().r, this->m_texts[i].getFillColor().g, this->m_texts[i].getFillColor().b, sf::Uint8(100.f)));
			this->m_backgrounds[i].a = sf::Uint8(100.f);
		}
		else
		{
			this->m_texts[i].setFillColor(sf::Color(this->m_texts[i].getFillColor().r, this->m_texts[i].getFillColor().g, this->m_texts[i].getFillColor().b, sf::Uint8(255.f)));
			this->m_backgrounds[i].a = sf::Uint8(255.f);
		}

		if (this->m_values[i] < 0.f)
		{
			this->m_values[i] = 0.f;
		}

		if (this->m_values[i] > 1.f)
		{
			this->m_values[i] = 1.f;
		}

		this->m_texts[i].setString(this->m_names[i] + ": " + std::to_string(((int)(this->m_values[i] * 100))));
		this->current_values[i].setSize(sf::Vector2f(this->m_shapes[i].getSize().x * this->m_values[i], this->m_shapes[i].getSize().y));
	}
}

void Slider::load_data()
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
		float value = 0.f;
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
			if (type == "SLIDER")
			{
				this->m_count++;

				this->m_shapes.push_back(sf::RectangleShape());
				this->current_values.push_back(sf::RectangleShape());
				this->m_values.push_back(0.f);
				this->m_backgrounds.push_back(sf::Color());
				this->m_texts.push_back(sf::Text());
				this->m_names.push_back("");

				data >> string >> value >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

				if (string == "-")
				{
					this->m_texts[this->m_count - 1].setString("");
				}
				else
				{
					this->m_texts[this->m_count - 1].setString(string);
				}
				this->m_values[this->m_count - 1] = value;
				this->m_shapes[this->m_count - 1].setSize(size);
				this->m_shapes[this->m_count - 1].setPosition(position);
				this->m_shapes[this->m_count - 1].setFillColor(sf::Color(r, g, b, a));
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

const bool Slider::getValue(unsigned short int number)
{
	return this->m_values[number];
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
		target.draw(this->current_values[i], states);
	}
}

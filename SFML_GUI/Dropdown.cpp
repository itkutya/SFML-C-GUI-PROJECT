#include "pch.h"

#include "Dropdown.h"

Dropdown::Dropdown()
{
	this->load_data();

	if (!this->m_font.loadFromFile("resources/sansation.ttf"))
	{
		throw std::runtime_error("Failed to find font!");
	}

	//Dropdown
	this->m_pressed = false;
	this->active_element = 15;
	this->show_list = false;

	this->make_a_list();
	for (std::size_t i = 0; i < this->list.size(); ++i)
	{
		this->elements[i].setSize(sf::Vector2f(this->m_shapes[0].getSize().x, this->m_shapes[0].getSize().y));
		this->elements[i].setPosition(sf::Vector2f(this->m_shapes[0].getPosition().x, this->m_shapes[0].getPosition().y + ((i + 1) * this->m_shapes[0].getGlobalBounds().height)));
		this->elements[i].setFillColor(this->m_shapes[0].getFillColor());
		this->elements[i].setOutlineThickness(this->m_shapes[0].getOutlineThickness());
		this->elements[i].setOutlineColor(this->m_shapes[0].getOutlineColor());
		this->backgrounds[i] = this->m_backgrounds[0];

		this->options[i].setString(this->list[i]);

		std::string l = this->options[i].getString();
		std::size_t length = l.length();

		this->options[i].setFont(this->m_font);
		this->options[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
		this->options[i].setPosition(this->elements[i].getPosition().x + (this->elements[i].getGlobalBounds().width / 2.f) - this->options[i].getGlobalBounds().width / 2.f,
									this->elements[i].getPosition().y + (this->elements[i].getGlobalBounds().height / 2.f) - this->options[i].getGlobalBounds().height / 2.f - 5.f);
	}

	//Text
	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		std::string l = this->m_texts[i].getString();
		std::size_t length = l.length();

		std::string le = this->active_text[i].getString();
		std::size_t length2 = le.length();

		if (length > 0 && length < 25)
		{
			if (this->m_texts[i].getString() != "")
			{
				this->m_texts[i].setFont(this->m_font);
				this->m_texts[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
				this->m_texts[i].setPosition(this->m_shapes[i].getPosition().x - this->m_texts[i].getGlobalBounds().width - 15.f,
											this->m_shapes[i].getPosition().y + (this->m_shapes[i].getGlobalBounds().height / 2.f) - this->m_texts[i].getGlobalBounds().height / 2.f - 5.f);
			}
		}

		this->active_text[i].setString(this->list[this->active_element]);
		this->active_text[i].setFont(this->m_font);
		this->active_text[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
		this->active_text[i].setPosition(this->m_shapes[i].getPosition().x + (this->m_shapes[i].getGlobalBounds().width / 2.f) - this->active_text[i].getGlobalBounds().width / 2.f,
										this->m_shapes[i].getPosition().y + (this->m_shapes[i].getGlobalBounds().height / 2.f) - this->active_text[i].getGlobalBounds().height / 2.f - 5.f);
	}
}

Dropdown::~Dropdown()
{

}

void Dropdown::update(const sf::Vector2f& mousePos, sf::Event& event)
{
	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		this->active_text[i].setString(this->list[this->active_element]);

		if (this->m_shapes[i].getGlobalBounds().contains(mousePos))
		{
			this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 2, this->m_backgrounds[i].g / 2, this->m_backgrounds[i].b / 2, this->m_backgrounds[i].a));
			if (event.type == sf::Event::MouseButtonPressed && !this->m_pressed && !this->show_list)
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a));
				this->m_pressed = true;
				this->show_list = true;
			}
			else if (event.type == sf::Event::MouseButtonPressed && !this->m_pressed && this->show_list)
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a));
				this->m_pressed = true;
				this->show_list = false;
			}

		}
		else
		{
			this->m_shapes[i].setFillColor(this->m_backgrounds[i]);
		}

		if (this->show_list)
		{
			this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a / 3));
		}
	}

	if (this->show_list)
	{
		for (std::size_t i = 0; i < this->list.size(); ++i)
		{
			if (this->elements[i].getGlobalBounds().contains(mousePos))
			{
				this->elements[i].setFillColor(sf::Color(this->backgrounds[i].r / 2, this->backgrounds[i].g / 2, this->backgrounds[i].b / 2, this->backgrounds[i].a));
				if (event.type == sf::Event::MouseButtonPressed && !this->m_pressed)
				{
					this->active_element = (int)i;
					this->m_pressed = true;
					this->show_list = false;
				}
			}
			else
			{
				this->elements[i].setFillColor(this->backgrounds[i]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				this->elements[i].setPosition(this->elements[i].getPosition().x, this->elements[i].getPosition().y + 15.f);
				this->options[i].setPosition(this->elements[i].getPosition().x + (this->elements[i].getGlobalBounds().width / 2.f) - this->options[i].getGlobalBounds().width / 2.f,
											this->elements[i].getPosition().y + (this->elements[i].getGlobalBounds().height / 2.f) - this->options[i].getGlobalBounds().height / 2.f - 5.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->elements[i].setPosition(this->elements[i].getPosition().x, this->elements[i].getPosition().y - 15.f);
				this->options[i].setPosition(this->elements[i].getPosition().x + (this->elements[i].getGlobalBounds().width / 2.f) - this->options[i].getGlobalBounds().width / 2.f,
											this->elements[i].getPosition().y + (this->elements[i].getGlobalBounds().height / 2.f) - this->options[i].getGlobalBounds().height / 2.f - 5.f);
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		this->m_pressed = false;
	}
}

void Dropdown::load_data()
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
			if (type == "DROPDOWN")
			{
				this->m_count++;

				this->m_shapes.push_back(sf::RectangleShape());
				this->m_backgrounds.push_back(sf::Color());
				this->m_texts.push_back(sf::Text());
				this->active_text.push_back(sf::Text());

				data >> string >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

				if (string == "-")
				{
					this->m_texts[this->m_count - 1].setString("");
				}
				else
				{
					this->m_texts[this->m_count - 1].setString(string);
				}

				this->m_shapes[this->m_count - 1].setSize(size);
				this->m_shapes[this->m_count - 1].setPosition(position);
				this->m_shapes[this->m_count - 1].setFillColor(sf::Color(r, g, b, a));
				this->m_shapes[this->m_count - 1].setOutlineThickness(2.f);
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

const int Dropdown::getActiveElement()
{
	return this->active_element;
}

sf::VideoMode Dropdown::setActiveElement()
{
	return this->modes[this->active_element];
}

void Dropdown::make_a_list()
{
	this->modes = sf::VideoMode::getFullscreenModes();

	for (std::size_t i = 0; i < this->modes.size(); ++i)
	{
		this->list.push_back(std::to_string(this->modes[i].width) + "x" + std::to_string(this->modes[i].height));
	}

	for (std::size_t i = 0; i < this->list.size(); ++i)
	{
		this->elements.push_back(sf::RectangleShape());
		this->backgrounds.push_back(sf::Color());
		this->options.push_back(sf::Text());
	}
}

void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (std::size_t i = 0; i < this->m_count; ++i)
	{
		//states.texture = &this->m_textures[i];
		target.draw(this->m_shapes[i], states);
		target.draw(this->active_text[i], states);
		if (this->m_texts[i].getString() != "")
		{
			target.draw(this->m_texts[i], states);
		}
	}
	if (this->show_list)
	{
		for (std::size_t i = 0; i < this->list.size(); ++i)
		{
			if (this->elements[i].getPosition().y < this->m_shapes[0].getPosition().y + (this->elements[i].getGlobalBounds().height * 6) 
				&& this->elements[i].getPosition().y > this->m_shapes[0].getPosition().y + this->m_shapes[0].getGlobalBounds().height)
			{
				target.draw(this->elements[i], states);
				target.draw(this->options[i], states);
			}
		}
	}
}

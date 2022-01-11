#include "pch.h"

#include "GUI.h"

namespace GUI
{
	//Button
	Button::Button()
	{
		if (!this->m_font.loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

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
			unsigned short int m_count = 0;
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
				if (type == "BUTTON")
				{
					m_count++;

					data >> string >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

					this->m_shapes.push_back(sf::RectangleShape(size));
					this->m_backgrounds.push_back(sf::Color(r, g, b, a));
					this->m_states.push_back(false);

					this->m_shapes[m_count - 1].setPosition(position);
					this->m_shapes[m_count - 1].setFillColor(sf::Color(r, g, b, a));
					this->m_shapes[m_count - 1].setOutlineThickness(2.f);
					this->m_shapes[m_count - 1].setOutlineColor(sf::Color(255, 255, 255, a));

					if (string != "-")
					{
						this->m_texts.push_back(sf::Text(string, this->m_font));

						for (std::size_t i = 0; i < this->m_texts.size(); ++i)
						{
							this->m_texts[i].setFillColor(sf::Color(t_r, t_g, t_b, t_a));

							std::string l = this->m_texts[i].getString();
							std::size_t length = l.length();

							if (length > 0 && length < 25)
							{
								this->m_texts[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
								this->m_texts[i].setPosition(this->m_shapes[m_count - 1].getPosition().x + (this->m_shapes[m_count - 1].getGlobalBounds().width / 2.f) - this->m_texts[i].getGlobalBounds().width / 2.f,
															this->m_shapes[m_count - 1].getPosition().y + (this->m_shapes[m_count - 1].getGlobalBounds().height / 2.f) - this->m_texts[i].getGlobalBounds().height / 2.f - 5.f);
							}
						}
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open data file.");
		}
		data.close();
	}
	Button::~Button()
	{

	}
	void Button::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
		{
			this->m_states[i] = false;
			if (this->m_shapes[i].getGlobalBounds().contains(mousePos))
			{
				this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 2, this->m_backgrounds[i].g / 2, this->m_backgrounds[i].b / 2, this->m_backgrounds[i].a));
				if (event.type == sf::Event::MouseButtonPressed && !this->m_pressed)
				{
					this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a));
					this->m_pressed = true;
					this->m_states[i] = true;
				}
			}
			else
			{
				this->m_shapes[i].setFillColor(this->m_backgrounds[i]);
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			this->m_pressed = false;
		}
	}
	const bool Button::onButtonClick(unsigned short int index)
	{
		return this->m_states[index];
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shapes.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
			{
				target.draw(this->m_shapes[i], states);
			}
		}

		if (this->m_texts.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_texts.size(); ++i)
			{
				target.draw(this->m_texts[i], states);
			}
		}
	}
	//Toggle
	Toggle::Toggle()
	{
		if (!this->m_font.loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

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
			unsigned short int m_count = 0;
			std::string type = "";
			std::string string = "";
			bool state = false;
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
					m_count++;

					data >> string >> state >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

					this->m_shapes.push_back(sf::RectangleShape(size));
					this->m_backgrounds.push_back(sf::Color(r, g, b, a));
					this->m_states.push_back(state);

					this->m_shapes[m_count - 1].setPosition(position);
					this->m_shapes[m_count - 1].setFillColor(sf::Color(r, g, b, a));
					this->m_shapes[m_count - 1].setOutlineThickness(5.f);
					this->m_shapes[m_count - 1].setOutlineColor(sf::Color(255, 255, 255, a));

					if (string != "-")
					{
						this->m_texts.push_back(sf::Text(string, this->m_font));

						for (std::size_t i = 0; i < this->m_texts.size(); ++i)
						{
							this->m_texts[i].setFillColor(sf::Color(t_r, t_g, t_b, t_a));

							std::string l = this->m_texts[i].getString();
							std::size_t length = l.length();

							this->m_texts[i].setCharacterSize((unsigned int)(24 - (length * 0.15)));
							this->m_texts[i].setPosition(this->m_shapes[m_count - 1].getPosition().x + (this->m_shapes[m_count - 1].getGlobalBounds().width / 2.f) - this->m_texts[i].getGlobalBounds().width - this->m_shapes[m_count - 1].getGlobalBounds().width,
														this->m_shapes[m_count - 1].getPosition().y + (this->m_shapes[m_count - 1].getGlobalBounds().height / 2.f) - this->m_texts[i].getGlobalBounds().height / 2.f - 5.f);
						}
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open data file.");
		}
		data.close();
	}
	Toggle::~Toggle()
	{

	}
	void Toggle::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
		{
			if (this->m_shapes[i].getGlobalBounds().contains(mousePos))
			{
				if (event.type == sf::Event::MouseButtonPressed && !this->m_states[i] && !this->m_pressed)
				{
					this->m_shapes[i].setFillColor(sf::Color(this->m_backgrounds[i].r / 3, this->m_backgrounds[i].g / 3, this->m_backgrounds[i].b / 3, this->m_backgrounds[i].a));
					this->m_states[i] = true;
					this->m_pressed = true;
				}
				else if (event.type == sf::Event::MouseButtonPressed && this->m_states[i] && !this->m_pressed)
				{
					this->m_shapes[i].setFillColor(this->m_backgrounds[i]);
					this->m_states[i] = false;
					this->m_pressed = true;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			this->m_pressed = false;
		}
	}
	const bool Toggle::getState(unsigned short int index)
	{
		return this->m_states[index];
	}
	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shapes.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
			{
				target.draw(this->m_shapes[i], states);
			}
		}

		if (this->m_texts.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_texts.size(); ++i)
			{
				target.draw(this->m_texts[i], states);
			}
		}
	}
}
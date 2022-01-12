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

					this->m_shapes.emplace_back(std::make_unique<sf::RectangleShape>(size));
					this->m_backgrounds.emplace_back(std::make_unique<sf::Color>(r, g, b, a));
					this->m_states.emplace_back(std::make_unique<bool>(false));

					this->m_shapes[m_count - 1]->setPosition(position);
					this->m_shapes[m_count - 1]->setFillColor(sf::Color(r, g, b, a));
					this->m_shapes[m_count - 1]->setOutlineThickness(2.f);
					this->m_shapes[m_count - 1]->setOutlineColor(sf::Color(255, 255, 255, a));

					if (string != "-")
					{
						this->m_texts.emplace_back(std::make_unique<sf::Text>(string, this->m_font));

						this->m_texts[m_count - 1]->setFillColor(sf::Color(t_r, t_g, t_b, t_a));

						std::string l = this->m_texts[m_count - 1]->getString();
						std::size_t length = l.length();

						if (length > 0 && length < 25)
						{
							this->m_texts[m_count - 1]->setCharacterSize((unsigned int)(24 - (length * 0.15)));
							this->m_texts[m_count - 1]->setPosition(this->m_shapes[m_count - 1]->getPosition().x + (this->m_shapes[m_count - 1]->getGlobalBounds().width / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().width / 2.f,
																	this->m_shapes[m_count - 1]->getPosition().y + (this->m_shapes[m_count - 1]->getGlobalBounds().height / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().height / 2.f - 5.f);
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
			*this->m_states[i] = false;
			if (this->m_shapes[i]->getGlobalBounds().contains(mousePos))
			{
				this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 2, this->m_backgrounds[i]->g / 2, this->m_backgrounds[i]->b / 2, this->m_backgrounds[i]->a));
				if (event.type == sf::Event::MouseButtonPressed && !this->m_pressed)
				{
					this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 3, this->m_backgrounds[i]->g / 3, this->m_backgrounds[i]->b / 3, this->m_backgrounds[i]->a));
					*this->m_states[i] = true;
					this->m_pressed = true;
				}
			}
			else
			{
				this->m_shapes[i]->setFillColor(*this->m_backgrounds[i]);
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			this->m_pressed = false;
		}
	}
	const bool Button::onButtonClick(unsigned short int index)
	{
		return *this->m_states[index];
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shapes.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
			{
				target.draw(*this->m_shapes[i], states);
			}
		}

		if (this->m_texts.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_texts.size(); ++i)
			{
				target.draw(*this->m_texts[i], states);
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

					this->m_shapes.emplace_back(std::make_unique<sf::RectangleShape>(size));
					this->m_backgrounds.emplace_back(std::make_unique<sf::Color>(r, g, b, a));
					this->m_states.emplace_back(std::make_unique<bool>(state));

					this->m_shapes[m_count - 1]->setPosition(position);
					this->m_shapes[m_count - 1]->setFillColor(sf::Color(r, g, b, a));
					this->m_shapes[m_count - 1]->setOutlineThickness(5.f);
					this->m_shapes[m_count - 1]->setOutlineColor(sf::Color(255, 255, 255, a));

					if (string != "-")
					{
						this->m_texts.emplace_back(std::make_unique<sf::Text>(string, this->m_font));

						this->m_texts[m_count - 1]->setFillColor(sf::Color(t_r, t_g, t_b, t_a));

						std::string l = this->m_texts[m_count - 1]->getString();
						std::size_t length = l.length();

						this->m_texts[m_count - 1]->setCharacterSize((unsigned int)(24 - (length * 0.15)));
						this->m_texts[m_count - 1]->setPosition(this->m_shapes[m_count - 1]->getPosition().x + (this->m_shapes[m_count - 1]->getGlobalBounds().width / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().width - this->m_shapes[m_count - 1]->getGlobalBounds().width,
																this->m_shapes[m_count - 1]->getPosition().y + (this->m_shapes[m_count - 1]->getGlobalBounds().height / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().height / 2.f - 5.f);

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
			if (this->m_shapes[i]->getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonPressed)
			{
				if (!*this->m_states[i] && !this->m_pressed)
				{
					this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 3, this->m_backgrounds[i]->g / 3, this->m_backgrounds[i]->b / 3, this->m_backgrounds[i]->a));
					*this->m_states[i] = true;
					this->m_pressed = true;
				}
				if (*this->m_states[i] && !this->m_pressed)
				{
					this->m_shapes[i]->setFillColor(*this->m_backgrounds[i]);
					*this->m_states[i] = false;
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
		return *this->m_states[index];
	}
	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shapes.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
			{
				target.draw(*this->m_shapes[i], states);
			}
		}

		if (this->m_texts.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_texts.size(); ++i)
			{
				target.draw(*this->m_texts[i], states);
			}
		}
	}
	//Slider
	Slider::Slider()
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
					m_count++;

					data >> string >> value >> size.x >> size.y >> position.x >> position.y >> r >> g >> b >> a >> t_r >> t_g >> t_b >> t_a;

					this->m_shapes.emplace_back(std::make_unique<sf::RectangleShape>(size));
					this->current_values.emplace_back(std::make_unique<sf::RectangleShape>(size));
					this->m_values.emplace_back(std::make_unique<float>(value));
					this->m_backgrounds.emplace_back(std::make_unique<sf::Color>(r, g, b, a));

					this->m_shapes[m_count - 1]->setPosition(position);
					this->m_shapes[m_count - 1]->setFillColor(sf::Color(r, g, b, a));

					this->current_values[m_count - 1]->setPosition(this->m_shapes[m_count - 1]->getPosition());
					this->current_values[m_count - 1]->setFillColor(sf::Color(this->m_backgrounds[m_count - 1]->r / 2, this->m_backgrounds[m_count - 1]->g / 2, this->m_backgrounds[m_count - 1]->b / 2, this->m_backgrounds[m_count - 1]->a));

					if (string != "-")
					{
						this->m_texts.emplace_back(std::make_unique<sf::Text>(string, this->m_font));
						this->m_string.emplace_back(std::make_unique<std::string>(string));

						this->m_texts[m_count - 1]->setFillColor(sf::Color(t_r, t_g, t_b, t_a));

						std::string l = this->m_texts[m_count - 1]->getString();
						std::size_t length = l.length();

						this->m_texts[m_count - 1]->setCharacterSize((unsigned int)(24 - (length * 0.15)));
						this->m_texts[m_count - 1]->setPosition(this->m_shapes[m_count - 1]->getPosition().x + (this->m_shapes[m_count - 1]->getGlobalBounds().width / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().width / 2.f - 10.f,
																this->m_shapes[m_count - 1]->getPosition().y + (this->m_shapes[m_count - 1]->getGlobalBounds().height / 2.f) - this->m_texts[m_count - 1]->getGlobalBounds().height / 2.f - this->m_shapes[m_count - 1]->getGlobalBounds().height - 10.f);
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
	Slider::~Slider()
	{

	}
	void Slider::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
		{
			if (this->m_shapes[i]->getGlobalBounds().contains(mousePos))
			{
				this->m_shapes[i]->setFillColor(*this->m_backgrounds[i]);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 3, this->m_backgrounds[i]->g / 3, this->m_backgrounds[i]->b, this->m_backgrounds[i]->a));
					*this->m_values[i] -= 0.01f;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 3, this->m_backgrounds[i]->g / 3, this->m_backgrounds[i]->b, this->m_backgrounds[i]->a));
					*this->m_values[i] += 0.01f;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->m_shapes[i]->setFillColor(sf::Color(this->m_backgrounds[i]->r / 3, this->m_backgrounds[i]->g / 3, this->m_backgrounds[i]->b, this->m_backgrounds[i]->a));
					*this->m_values[i] = ((this->m_shapes[i]->getPosition().x - mousePos.x) / this->m_shapes[i]->getGlobalBounds().width) * -1;
				}
			}
			else
			{
				this->m_shapes[i]->setFillColor(*this->m_backgrounds[i]);
			}

			if (*this->m_values[i] == 0.0f)
			{
				this->m_texts[i]->setFillColor(sf::Color(this->m_texts[i]->getFillColor().r, this->m_texts[i]->getFillColor().g, this->m_texts[i]->getFillColor().b, 100));
				this->m_backgrounds[i]->a = 100;
			}
			else
			{
				this->m_texts[i]->setFillColor(sf::Color(this->m_texts[i]->getFillColor().r, this->m_texts[i]->getFillColor().g, this->m_texts[i]->getFillColor().b, 255));
				this->m_backgrounds[i]->a = 255;
			}

			if (*this->m_values[i] < 0.f)
			{
				*this->m_values[i] = 0.f;
			}
			else if (*this->m_values[i] > 1.f)
			{
				*this->m_values[i] = 1.f;
			}

			this->current_values[i]->setSize(sf::Vector2f(this->m_shapes[i]->getSize().x * *this->m_values[i], this->m_shapes[i]->getSize().y));
		}

		for (std::size_t i = 0; i < this->m_texts.size(); ++i)
		{
			this->m_texts[i]->setString(*this->m_string[i] + ": " + std::to_string(((int)(*this->m_values[i] * 100))));
		}
	}
	const float Slider::getValue(unsigned short int index)
	{
		return *this->m_values[index];
	}
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shapes.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_shapes.size(); ++i)
			{
				target.draw(*this->m_shapes[i], states);
				target.draw(*this->current_values[i], states);
			}
		}

		if (this->m_texts.size() > 0)
		{
			for (std::size_t i = 0; i < this->m_texts.size(); ++i)
			{
				target.draw(*this->m_texts[i], states);
			}
		}
	}
}
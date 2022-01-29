#include "pch.h"

#include "GUI.h"

namespace GUI
{
	//Button
	Button::Button(const char* name, std::function<void()> func)
	{
		this->function = func;

		this->m_font = std::make_unique<sf::Font>();
		if (!this->m_font->loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type >> string)
			{
				if (type == "BUTTON" && string == name)
				{
					file >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

					this->m_shape = std::make_unique<sf::RectangleShape>(size);
					this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
					this->m_state = std::make_unique<bool>(false);
					this->m_pressed = std::make_unique<bool>(false);

					this->m_shape->setPosition(position);
					this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));
					this->m_shape->setOutlineThickness(2.f);
					this->m_shape->setOutlineColor(sf::Color(255, 255, 255, color.a));

					if (string != "-")
					{
						this->m_text = std::make_unique<sf::Text>(string, *this->m_font);

						this->m_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

						std::string l = this->m_text->getString();
						std::size_t length = l.length();

						if (length > 0 && length < 25)
						{
							this->m_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->m_text->getGlobalBounds().width / 2.f,
													  this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->m_text->getGlobalBounds().height / 2.f - 5.f);
						}
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open the file.");
		}
		file.close();
	}
	Button::~Button()
	{
	}
	void Button::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			(*this->m_state) = false;
			if (this->m_shape->getGlobalBounds().contains(mousePos))
			{
				this->m_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));
				if (event.type == sf::Event::MouseButtonPressed && !(*this->m_pressed))
				{
					(this->function)();
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_state) = true;
					(*this->m_pressed) = true;
				}
			}
			else
			{
				this->m_shape->setFillColor(*this->m_background);
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				(*this->m_pressed) = false;
			}
		}
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shape != nullptr)
		{
			target.draw(*this->m_shape, states);
		}
		if (this->m_text != nullptr)
		{
			target.draw(*this->m_text, states);
		}
	}
	//Toggle
	Toggle::Toggle(const char* name, std::function<void()> func)
	{
		this->function = func;

		this->m_font = std::make_unique<sf::Font>();
		if (!this->m_font->loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			bool state = false;
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type >> string)
			{
				if (type == "TOGGLE" && string == name)
				{
					file >> state >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

					this->m_shape = std::make_unique<sf::RectangleShape>(size);
					this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
					this->m_state = std::make_unique<bool>(false);
					this->m_pressed = std::make_unique<bool>(false);

					this->m_shape->setPosition(position);
					this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));
					this->m_shape->setOutlineThickness(2.f);
					this->m_shape->setOutlineColor(sf::Color(255, 255, 255, color.a));

					if (string != "-")
					{
						this->m_text = std::make_unique<sf::Text>(string, *this->m_font);

						this->m_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

						std::string l = this->m_text->getString();
						std::size_t length = l.length();

						this->m_text->setCharacterSize((unsigned int)(24 - (length * 0.15)));
						this->m_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->m_text->getGlobalBounds().width - this->m_shape->getGlobalBounds().width,
												  this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->m_text->getGlobalBounds().height / 2.f - 5.f);
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();
	}
	Toggle::~Toggle()
	{
	}
	void Toggle::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			if (this->m_shape->getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonPressed)
			{
				if (!(*this->m_state) && !(*this->m_pressed))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_state) = true;
					(*this->m_pressed) = true;
					(this->function)();
				}
				else if ((*this->m_state) && !(*this->m_pressed))
				{
					this->m_shape->setFillColor(*this->m_background);
					(*this->m_state) = false;
					(*this->m_pressed) = true;
					(this->function)();
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				(*this->m_pressed) = false;
			}
		}
	}
	const bool Toggle::getState()
	{
		return (*this->m_state);
	}
	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shape != nullptr)
		{
			target.draw(*this->m_shape, states);
		}

		if (this->m_text != nullptr)
		{
			target.draw(*this->m_text, states);
		}
	}
	//Slider
	Slider::Slider(const char* name, std::function<void()> func)
	{
		this->function = func;

		this->m_font = std::make_unique<sf::Font>();
		if (!this->m_font->loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			float value = 0.f;
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type >> string)
			{
				if (type == "SLIDER" && string == name)
				{
					file >> value >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

					this->m_shape = std::make_unique<sf::RectangleShape>(size);
					this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
					this->c_shape = std::make_unique<sf::RectangleShape>(size);
					this->c_value = std::make_unique<float>(value);

					this->m_shape->setPosition(position);
					this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));

					this->c_shape->setPosition(this->m_shape->getPosition());
					this->c_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));

					if (string != "-")
					{
						this->m_text = std::make_unique<sf::Text>(string, *this->m_font);
						this->c_string = std::make_unique<std::string>(string);

						this->m_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

						std::string l = this->m_text->getString();
						std::size_t length = l.length();

						this->m_text->setCharacterSize((unsigned int)(24 - (length * 0.15)));
						this->m_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->m_text->getGlobalBounds().width / 2.f - 10.f,
												  this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->m_text->getGlobalBounds().height / 2.f - this->m_shape->getGlobalBounds().height - 10.f);
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();
	}
	Slider::~Slider()
	{
	}
	void Slider::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			float value = (*this->c_value);
			if (this->m_shape->getGlobalBounds().contains(mousePos))
			{
				this->m_shape->setFillColor(*this->m_background);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->c_value) -= 0.01f;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->c_value) += 0.01f;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->c_value) = ((this->m_shape->getPosition().x - mousePos.x) / this->m_shape->getGlobalBounds().width) * -1;
				}
			}
			else
			{
				this->m_shape->setFillColor(*this->m_background);
			}

			if ((*this->c_value) == 0.0f)
			{
				this->m_text->setFillColor(sf::Color(this->m_text->getFillColor().r, this->m_text->getFillColor().g, this->m_text->getFillColor().b, 100));
				this->m_background->a = 100;
			}
			else
			{
				this->m_text->setFillColor(sf::Color(this->m_text->getFillColor().r, this->m_text->getFillColor().g, this->m_text->getFillColor().b, 255));
				this->m_background->a = 255;
			}

			if ((*this->c_value) < 0.f)
			{
				(*this->c_value) = 0.f;
			}
			else if ((*this->c_value) > 1.f)
			{
				(*this->c_value) = 1.f;
			}

			if (value != (*this->c_value))
			{
				(this->function)();
			}
			this->c_shape->setSize(sf::Vector2f(this->m_shape->getSize().x * (*this->c_value), this->m_shape->getSize().y));
			this->m_text->setString((*this->c_string) + ": " + std::to_string(((int)((*this->c_value) * 100))));
		}
	}
	const float Slider::getValue()
	{
		return (*this->c_value);
	}
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shape != nullptr)
		{
			target.draw(*this->m_shape, states);
			target.draw(*this->c_shape, states);
		}
		if (this->m_text != nullptr)
		{
			target.draw(*this->m_text, states);
		}
	}
	//Dropdown
	Dropdown::Dropdown(std::vector<std::string>& list, const char* name, std::function<void()> func)
	{
		this->function = func;

		this->m_font = std::make_unique<sf::Font>();
		if (!this->m_font->loadFromFile("resources/sansation.ttf"))
		{
			throw std::runtime_error("Failed to find font!");
		}

		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type >> string)
			{
				if (type == "DROPDOWN" && string == name)
				{
					file >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

					this->m_shape = std::make_unique<sf::RectangleShape>(size);
					this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
					this->a_element = std::make_unique<int>(0);
					this->show_list = std::make_unique<bool>(false);
					this->m_pressed = std::make_unique<bool>(false);

					this->m_shape->setPosition(position);
					this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));
					this->m_shape->setOutlineThickness(2.f);
					this->m_shape->setOutlineColor(sf::Color(255, 255, 255, color.a));

					for (std::size_t i = 0; i < list.size(); ++i)
					{
						this->c_list.emplace_back(std::make_unique<std::string>(list[i]));
					}
					this->a_text = std::make_unique<sf::Text>(*this->c_list[*this->a_element], *this->m_font);

					std::string al = this->a_text->getString();
					std::size_t alength = al.length();

					this->a_text->setCharacterSize((unsigned int)(24 - (alength * 0.15)));
					this->a_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->a_text->getGlobalBounds().width / 2.f,
						this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->a_text->getGlobalBounds().height / 2.f - 5.f);

					if (string != "-")
					{
						this->m_text = std::make_unique<sf::Text>(string, *this->m_font);

						this->m_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

						std::string l = this->m_text->getString();
						std::size_t length = l.length();

						if (length > 0 && length < 25)
						{
							this->m_text->setCharacterSize((unsigned int)(24 - (length * 0.15)));
							this->m_text->setPosition(this->m_shape->getPosition().x - this->m_text->getGlobalBounds().width - 15.f,
								this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->m_text->getGlobalBounds().height / 2.f - 5.f);
						}
					}
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();

		for (std::size_t i = 0; i < list.size(); ++i)
		{
			this->c_elements.emplace_back(std::make_unique<sf::RectangleShape>(this->m_shape->getSize()));
			this->c_backgrounds.emplace_back(std::make_unique<sf::Color>(this->m_background->r, this->m_background->g, this->m_background->b, this->m_background->a));
			this->c_options.emplace_back(std::make_unique<sf::Text>(list[i], *this->m_font));

			this->c_elements[i]->setPosition(sf::Vector2f(this->m_shape->getPosition().x, this->m_shape->getPosition().y + ((i + 1) * this->m_shape->getGlobalBounds().height)));
			this->c_elements[i]->setFillColor(this->m_shape->getFillColor());
			this->c_elements[i]->setOutlineThickness(this->m_shape->getOutlineThickness());
			this->c_elements[i]->setOutlineColor(this->m_shape->getOutlineColor());

			std::string ol = this->c_options[i]->getString();
			std::size_t olength = ol.length();

			this->c_options[i]->setCharacterSize((unsigned int)(24 - (olength * 0.15)));
			this->c_options[i]->setPosition(this->c_elements[i]->getPosition().x + (this->c_elements[i]->getGlobalBounds().width / 2.f) - this->c_options[i]->getGlobalBounds().width / 2.f,
											this->c_elements[i]->getPosition().y + (this->c_elements[i]->getGlobalBounds().height / 2.f) - this->c_options[i]->getGlobalBounds().height / 2.f - 5.f);
		}

	}
	Dropdown::~Dropdown()
	{
	}
	void Dropdown::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			this->a_text->setString(*this->c_list[*this->a_element]);

			if (this->m_shape->getGlobalBounds().contains(mousePos))
			{
				this->m_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));
				if (event.type == sf::Event::MouseButtonPressed && !(*this->m_pressed) && !*this->show_list)
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_pressed) = true;
					(*this->show_list) = true;
				}
				else if (event.type == sf::Event::MouseButtonPressed && !(*this->m_pressed) && *this->show_list)
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_pressed) = true;
					(*this->show_list) = false;
				}
			}
			else
			{
				this->m_shape->setFillColor(*this->m_background);
			}

			if (*this->show_list)
			{
				this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a / 3));
			}

			if (this->c_list.size() > 0)
			{
				if (*this->show_list)
				{
					for (std::size_t i = 0; i < this->c_list.size(); ++i)
					{
						if (this->c_elements[i]->getGlobalBounds().contains(mousePos))
						{
							this->c_elements[i]->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));
							if (event.type == sf::Event::MouseButtonPressed && !(*this->m_pressed))
							{
								(*this->a_element) = (int)i;
								(*this->m_pressed) = true;
								(*this->show_list) = false;
								(this->function)();
							}
						}
						else
						{
							this->c_elements[i]->setFillColor(*this->m_background);
						}

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							this->c_elements[i]->setPosition(this->c_elements[i]->getPosition().x, this->c_elements[i]->getPosition().y + 15.f);
							this->c_options[i]->setPosition(this->c_elements[i]->getPosition().x + (this->c_elements[i]->getGlobalBounds().width / 2.f) - this->c_options[i]->getGlobalBounds().width / 2.f,
															this->c_elements[i]->getPosition().y + (this->c_elements[i]->getGlobalBounds().height / 2.f) - this->c_options[i]->getGlobalBounds().height / 2.f - 5.f);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							this->c_elements[i]->setPosition(this->c_elements[i]->getPosition().x, this->c_elements[i]->getPosition().y - 15.f);
							this->c_options[i]->setPosition(this->c_elements[i]->getPosition().x + (this->c_elements[i]->getGlobalBounds().width / 2.f) - this->c_options[i]->getGlobalBounds().width / 2.f,
															this->c_elements[i]->getPosition().y + (this->c_elements[i]->getGlobalBounds().height / 2.f) - this->c_options[i]->getGlobalBounds().height / 2.f - 5.f);
						}

						if (i == 0)
						{
							if (this->scrool > 0)
							{
								this->c_elements[0]->setPosition(this->c_elements[0]->getPosition().x, this->c_elements[0]->getPosition().y + 15.f);
								this->c_options[0]->setPosition(this->c_elements[0]->getPosition().x + (this->c_elements[0]->getGlobalBounds().width / 2.f) - this->c_options[0]->getGlobalBounds().width / 2.f,
																this->c_elements[0]->getPosition().y + (this->c_elements[0]->getGlobalBounds().height / 2.f) - this->c_options[0]->getGlobalBounds().height / 2.f - 5.f);

								this->scrool = 0;
							}
							else if (this->scrool < 0)
							{
								this->c_elements[0]->setPosition(this->c_elements[0]->getPosition().x, this->c_elements[0]->getPosition().y - 15.f);
								this->c_options[0]->setPosition(this->c_elements[0]->getPosition().x + (this->c_elements[0]->getGlobalBounds().width / 2.f) - this->c_options[0]->getGlobalBounds().width / 2.f,
																this->c_elements[0]->getPosition().y + (this->c_elements[0]->getGlobalBounds().height / 2.f) - this->c_options[0]->getGlobalBounds().height / 2.f - 5.f);

								this->scrool = 0;
							}
						}
						else
						{
							this->c_elements[i]->setPosition(sf::Vector2f(this->c_elements[0]->getPosition().x, this->c_elements[0]->getPosition().y + (i * this->c_elements[0]->getGlobalBounds().height)));
							this->c_options[i]->setPosition(this->c_elements[i]->getPosition().x + (this->c_elements[i]->getGlobalBounds().width / 2.f) - this->c_options[i]->getGlobalBounds().width / 2.f,
															this->c_elements[i]->getPosition().y + (this->c_elements[i]->getGlobalBounds().height / 2.f) - this->c_options[i]->getGlobalBounds().height / 2.f - 5.f);
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				(*this->m_pressed) = false;
			}
		}
	}
	const int Dropdown::getActiveElement()
	{
		return (*this->a_element);
	}
	void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (this->m_shape != nullptr)
		{
			target.draw(*this->m_shape, states);
			target.draw(*this->a_text, states);
			if (this->c_elements.size() > 0)
			{
				if (*this->show_list)
				{
					for (std::size_t i = 0; i < this->c_elements.size(); ++i)
					{
						target.draw(*this->c_elements[i], states);
						target.draw(*this->c_options[i], states);
					}
				}
			}
		}

		if (this->m_text != nullptr)
		{
			target.draw(*this->m_text, states);
		}
	}
	//Image
	Image::Image(const char* name)
	{
		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			std::string path = "";
			sf::IntRect area;
			sf::Vector2f size;
			sf::Vector2f position;

			while (file >> type >> string)
			{
				if (type == "IMAGE" && string == name)
				{
					file >> path >> area.left >> area.top >> area.width >> area.height >> size.x >> size.y >> position.x >> position.y;

					this->m_shape = std::make_unique<sf::RectangleShape>(size);
					this->m_shape->setPosition(position);
					this->m_shape->setOutlineThickness(2.f);
					this->m_shape->setOutlineColor(sf::Color(255, 255, 255, 255));

					this->m_texture = std::make_unique<sf::Texture>();

					this->m_texture->loadFromFile(path, area);
					this->m_texture->setSmooth(true);
					this->m_texture->setSrgb(true);
					this->m_shape->setTexture(&(*this->m_texture));
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();
	}
	Image::~Image()
	{
	}
	void Image::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->scrool > 0)
		{
			this->scrool = 0;
		}
		else if (this->scrool < 0)
		{
			this->scrool = 0;
		}
	}
	void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->m_shape != nullptr)
		{
			states.texture = &(*this->m_texture);
			target.draw(*this->m_shape, states);
		}
	}
	//Menu
	Menu::Menu()
	{

	}
	Menu::~Menu()
	{

	}
	void Menu::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		for (std::size_t i = 0; i < this->buttons.size(); ++i)
		{
			this->buttons[i]->update(mousePos, event);
		}
		for (std::size_t i = 0; i < this->toggles.size(); ++i)
		{
			this->toggles[i]->update(mousePos, event);
		}
		for (std::size_t i = 0; i < this->sliders.size(); ++i)
		{
			this->sliders[i]->update(mousePos, event);
		}
		for (std::size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			this->dropdowns[i]->update(mousePos, event);
		}
		for (std::size_t i = 0; i < this->images.size(); ++i)
		{
			this->images[i]->update(mousePos, event);
		}
	}
	const float Menu::getVersion()
	{
		std::fstream file("resources/gui.txt");
		if (file.is_open())
		{
			std::string string = "";
			float version = 0.f;
			while (file >> string)
			{
				if (string == "#VERSION")
				{
					file >> version;
					file.close();

					return version;
				}
			}
		}
		else
		{
			throw std::runtime_error("Cannot open data file.");
		}
		file.close();

		return 0.f;
	}
	const int Menu::getActiveElement(const char* name)
	{
		for (std::size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			if (this->dropdowns[i]->m_text->getString() == name)
			{
				return this->dropdowns[i]->getActiveElement();
			}
		}
		return 0;
	}
	const float Menu::getValue(const char* name)
	{
		for (std::size_t i = 0; i < this->sliders.size(); ++i)
		{
			if ((*this->sliders[i]->c_string) == name)
			{
				return this->sliders[i]->getValue() * 100.f;
			}
		}
		return 0.0f;
	}
	const bool Menu::getState(const char* name)
	{
		for (std::size_t i = 0; i < this->toggles.size(); ++i)
		{
			if (this->toggles[i]->m_text->getString() == name)
			{
				return this->toggles[i]->getState();
			}
		}
		return false;
	}
	void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (std::size_t i = 0; i < this->buttons.size(); ++i)
		{
			target.draw(*this->buttons[i]);
		}
		for (std::size_t i = 0; i < this->toggles.size(); ++i)
		{
			target.draw(*this->toggles[i]);
		}
		for (std::size_t i = 0; i < this->sliders.size(); ++i)
		{
			target.draw(*this->sliders[i]);
		}
		for (std::size_t i = 0; i < this->dropdowns.size(); ++i)
		{
			target.draw(*this->dropdowns[i]);
		}
		for (std::size_t i = 0; i < this->images.size(); ++i)
		{
			target.draw(*this->images[i]);
		}
	}
	void Menu::CreateButton(const char* name, std::function<void()> func)
	{
		this->buttons.push_back(std::make_unique<Button>(name, func));
	}
	void Menu::CreateToggle(const char* name, std::function<void()> func)
	{
		this->toggles.push_back(std::make_unique<Toggle>(name, func));
	}
	void Menu::CreateSlider(const char* name, std::function<void()> func)
	{
		this->sliders.push_back(std::make_unique<Slider>(name, func));
	}
	void Menu::CreateDropdown(const char* text, std::vector<std::string>& list, std::function<void()> func)
	{
		this->dropdowns.push_back(std::make_unique<Dropdown>(list, text, func));
	}
	void Menu::CreateImage(const char* name)
	{
		this->images.push_back(std::make_unique<Image>(name));
	}
}
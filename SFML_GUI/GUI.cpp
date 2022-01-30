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

		std::fstream file("resources/gui.txt", std::ios::in | std::ios::out);
		if (file.is_open())
		{
			std::string type = "";
			std::string string = "";
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type)
			{
				if (type == "BUTTON")
				{
					while (file >> string)
					{
						if (string == name)
						{
							file >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

							this->m_shape = std::make_unique<sf::RectangleShape>(size);
							this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
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
			}
		}
		else
		{
			throw std::runtime_error("Cannot open the file.");
		}
		file.close();

		std::ofstream myfile("resources/gui.txt", std::ios::app);
		if (myfile.is_open())
		{
			if (this->m_shape == nullptr)
			{
				std::string type = "BUTTON";
				std::string string = name;
				sf::Vector2f size = { 200, 100 };
				sf::Vector2f position = { 0, 0 };
				Color color = { 255, 255, 255, 255 };
				Color text_color = { 255, 255, 255, 255 };

				myfile.seekp(0, std::ios::end);
				myfile << '\n' << '\n' << type << '\n' << string << '\n' << size.x << " " << size.y << '\n' << position.x << " " << position.y << '\n' << color.r << " " << color.g << " " << color.b << " " << color.a << '\n' << text_color.r << " " << text_color.g << " " << text_color.b << " " << text_color.a;

				this->m_shape = std::make_unique<sf::RectangleShape>(size);
				this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
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
		else
			std::cout << "Unable to open file";
	}
	Button::~Button()
	{
	}
	void Button::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			if (this->m_shape->getGlobalBounds().contains(mousePos))
			{
				this->m_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));
				if (event.type == sf::Event::MouseButtonPressed && !(*this->m_pressed))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_pressed) = true;
					(this->function)();
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
			int state = 0;
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type)
			{
				if (type == "TOGGLE")
				{
					while (file >> string)
					{
						if (string == name)
						{
							file >> state >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

							this->m_shape = std::make_unique<sf::RectangleShape>(size);
							this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
							this->m_state = std::make_unique<int>(state);
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

							if ((*this->m_state) == 1)
							{
								this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
							}
							else if ((*this->m_state) == 0)
							{
								this->m_shape->setFillColor(*this->m_background);
							}
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

		std::ofstream myfile("resources/gui.txt", std::ios::app);
		if (myfile.is_open())
		{
			if (this->m_shape == nullptr)
			{
				std::string type = "TOGGLE";
				std::string string = name;
				int state = 0;
				sf::Vector2f size = { 200, 100 };
				sf::Vector2f position = { 0, 0 };
				Color color = { 255, 255, 255, 255 };
				Color text_color = { 255, 255, 255, 255 };

				myfile.seekp(0, std::ios::end);
				myfile << '\n' << '\n' << type << '\n' << string << '\n' << state << '\n' << size.x << " " << size.y << '\n' << position.x << " " << position.y << '\n' << color.r << " " << color.g << " " << color.b << " " << color.a << '\n' << text_color.r << " " << text_color.g << " " << text_color.b << " " << text_color.a;

				this->m_shape = std::make_unique<sf::RectangleShape>(size);
				this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
				this->m_state = std::make_unique<int>(state);
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

				if ((*this->m_state) == 1)
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
				}
				else if ((*this->m_state) == 0)
				{
					this->m_shape->setFillColor(*this->m_background);
				}
			}
		}
		else
			std::cout << "Unable to open file";
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
				if ((*this->m_state) == 0 && !(*this->m_pressed))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b / 3, this->m_background->a));
					(*this->m_state) = 1;
					(*this->m_pressed) = true;
					(this->function)();
				}
				else if ((*this->m_state) == 1 && !(*this->m_pressed))
				{
					this->m_shape->setFillColor(*this->m_background);
					(*this->m_state) = 0;
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
			int value = 0;
			sf::Vector2f size;
			sf::Vector2f position;
			Color color;
			Color text_color;

			while (file >> type)
			{
				if (type == "SLIDER")
				{
					while (file >> string)
					{
						if (string == name)
						{
							file >> value >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

							this->m_shape = std::make_unique<sf::RectangleShape>(size);
							this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
							this->c_shape = std::make_unique<sf::RectangleShape>(size);
							this->m_state = std::make_unique<int>(value);

							this->m_shape->setPosition(position);
							this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));

							this->c_shape->setPosition(this->m_shape->getPosition());
							this->c_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));

							if (string != "-")
							{
								this->m_text = std::make_unique<sf::Text>(string, *this->m_font);
								this->c_text = std::make_unique<sf::Text>(string, *this->m_font);

								this->c_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

								std::string l = this->c_text->getString();
								std::size_t length = l.length();

								this->c_text->setCharacterSize((unsigned int)(24 - (length * 0.15)));
								this->c_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->c_text->getGlobalBounds().width / 2.f - 10.f,
									this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->c_text->getGlobalBounds().height / 2.f - this->m_shape->getGlobalBounds().height - 10.f);
							}
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

		std::ofstream myfile("resources/gui.txt", std::ios::app);
		if (myfile.is_open())
		{
			if (this->m_shape == nullptr)
			{
				std::string type = "SLIDER";
				std::string string = name;
				int value = 100;
				sf::Vector2f size = { 200, 100 };
				sf::Vector2f position = { 0, 0 };
				Color color = { 255, 255, 255, 255 };
				Color text_color = { 255, 255, 255, 255 };

				myfile.seekp(0, std::ios::end);
				myfile << '\n' << '\n' << type << '\n' << string << '\n' << value << '\n' << size.x << " " << size.y << '\n' << position.x << " " << position.y << '\n' << color.r << " " << color.g << " " << color.b << " " << color.a << '\n' << text_color.r << " " << text_color.g << " " << text_color.b << " " << text_color.a;

				this->m_shape = std::make_unique<sf::RectangleShape>(size);
				this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
				this->c_shape = std::make_unique<sf::RectangleShape>(size);
				this->m_state = std::make_unique<int>(value);

				this->m_shape->setPosition(position);
				this->m_shape->setFillColor(sf::Color(color.r, color.g, color.b, color.a));

				this->c_shape->setPosition(this->m_shape->getPosition());
				this->c_shape->setFillColor(sf::Color(this->m_background->r / 2, this->m_background->g / 2, this->m_background->b / 2, this->m_background->a));

				if (string != "-")
				{
					this->m_text = std::make_unique<sf::Text>(string, *this->m_font);
					this->c_text = std::make_unique<sf::Text>(string, *this->m_font);

					this->c_text->setFillColor(sf::Color(text_color.r, text_color.g, text_color.b, text_color.a));

					std::string l = this->c_text->getString();
					std::size_t length = l.length();

					this->c_text->setCharacterSize((unsigned int)(24 - (length * 0.15)));
					this->c_text->setPosition(this->m_shape->getPosition().x + (this->m_shape->getGlobalBounds().width / 2.f) - this->c_text->getGlobalBounds().width / 2.f - 10.f,
						this->m_shape->getPosition().y + (this->m_shape->getGlobalBounds().height / 2.f) - this->c_text->getGlobalBounds().height / 2.f - this->m_shape->getGlobalBounds().height - 10.f);
				}
			}
		}
		else
			std::cout << "Unable to open file";
	}
	Slider::~Slider()
	{
	}
	void Slider::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			int value = (*this->m_state);
			if (this->m_shape->getGlobalBounds().contains(mousePos))
			{
				this->m_shape->setFillColor(*this->m_background);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->m_state) -= 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->m_state) += 1;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->m_shape->setFillColor(sf::Color(this->m_background->r / 3, this->m_background->g / 3, this->m_background->b, this->m_background->a));
					(*this->m_state) = (int)(((this->m_shape->getPosition().x - mousePos.x) / this->m_shape->getGlobalBounds().width) * -100);
				}
			}
			else
			{
				this->m_shape->setFillColor(*this->m_background);
			}

			if ((*this->m_state) == 0)
			{
				this->c_text->setFillColor(sf::Color(this->c_text->getFillColor().r, this->c_text->getFillColor().g, this->c_text->getFillColor().b, 100));
				this->m_background->a = 100;
			}
			else
			{
				this->c_text->setFillColor(sf::Color(this->c_text->getFillColor().r, this->c_text->getFillColor().g, this->c_text->getFillColor().b, 255));
				this->m_background->a = 255;
			}

			if ((*this->m_state) < 0)
			{
				(*this->m_state) = 0;
			}
			else if ((*this->m_state) > 100)
			{
				(*this->m_state) = 100;
			}

			if (value != (*this->m_state))
			{
				(this->function)();
			}
			this->c_shape->setSize(sf::Vector2f(this->m_shape->getSize().x * ((*this->m_state) / 100.f), this->m_shape->getSize().y));
			this->c_text->setString(this->m_text->getString() + ": " + std::to_string((*this->m_state)));
		}
	}
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (this->m_shape != nullptr)
		{
			target.draw(*this->m_shape, states);
			target.draw(*this->c_shape, states);
		}
		if (this->c_text != nullptr)
		{
			target.draw(*this->c_text, states);
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

			while (file >> type)
			{
				if (type == "DROPDOWN")
				{
					while (file >> string)
					{
						if (string == name)
						{
							file >> size.x >> size.y >> position.x >> position.y >> color.r >> color.g >> color.b >> color.a >> text_color.r >> text_color.g >> text_color.b >> text_color.a;

							this->m_shape = std::make_unique<sf::RectangleShape>(size);
							this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
							this->m_state = std::make_unique<int>(0);
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
							this->a_text = std::make_unique<sf::Text>(*this->c_list[*this->m_state], *this->m_font);

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
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();

		std::ofstream myfile("resources/gui.txt", std::ios::app);
		if (myfile.is_open())
		{
			if (this->m_shape == nullptr)
			{
				std::string type = "DROPDOWN";
				std::string string = name;
				sf::Vector2f size = { 200, 100 };
				sf::Vector2f position = { 0, 0 };
				Color color = { 255, 255, 255, 255 };
				Color text_color = { 255, 255, 255, 255 };

				myfile.seekp(0, std::ios::end);
				myfile << '\n' << '\n' << type << '\n' << string << '\n' << size.x << " " << size.y << '\n' << position.x << " " << position.y << '\n' << color.r << " " << color.g << " " << color.b << " " << color.a << '\n' << text_color.r << " " << text_color.g << " " << text_color.b << " " << text_color.a;

				this->m_shape = std::make_unique<sf::RectangleShape>(size);
				this->m_background = std::make_unique<sf::Color>(color.r, color.g, color.b, color.a);
				this->m_state = std::make_unique<int>(0);
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
				this->a_text = std::make_unique<sf::Text>(*this->c_list[*this->m_state], *this->m_font);

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
		else
			std::cout << "Unable to open file";

		if (this->m_shape != nullptr)
		{
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
	}
	Dropdown::~Dropdown()
	{
	}
	void Dropdown::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		if (this->m_shape != nullptr)
		{
			this->a_text->setString(*this->c_list[*this->m_state]);

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
								(*this->m_state) = (int)i;
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

			while (file >> type)
			{
				if (type == "IMAGE")
				{
					while (file >> string)
					{
						if (string == name)
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
			}
		}
		else
		{
			throw std::runtime_error("Cannot open file file.");
		}
		file.close();

		std::ofstream myfile("resources/gui.txt", std::ios::app);
		if (myfile.is_open())
		{
			if (this->m_shape == nullptr)
			{
				std::string type = "IMAGE";
				std::string string = name;
				std::string path = "resources/image.png";
				sf::IntRect area = { 0, 0, 1000, 1000 };
				sf::Vector2f size = { 200, 100 };
				sf::Vector2f position = { 0, 0 };

				myfile.seekp(0, std::ios::end);
				myfile << '\n' << '\n' << type << '\n' << string << '\n' << path << '\n' << area.left << " " << area.top << " " << area.width << " " << area.height << '\n' << size.x << " " << size.y << '\n' << position.x << " " << position.y;

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
		else
			std::cout << "Unable to open file";
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
	const int Menu::getState(const char* name)
	{
		for (std::size_t i = 0; i < this->widgets.size(); ++i)
		{
			if (this->widgets[i]->m_text != nullptr)
			{
				if (this->widgets[i]->m_text->getString() == name)
				{
					return (*this->widgets[i]->m_state);
				}
			}
		}
		return 0;
	}
	void Menu::update(const sf::Vector2f& mousePos, sf::Event& event)
	{
		for (std::size_t i = 0; i < this->widgets.size(); ++i)
		{
			this->widgets[i]->update(mousePos, event);
		}
	}
	void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (std::size_t i = 0; i < this->widgets.size(); ++i)
		{
			target.draw(*this->widgets[i]);
		}
	}
	void Menu::CreateButton(const char* name, std::function<void()> func)
	{
		this->widgets.push_back(std::make_unique<Button>(name, func));
	}
	void Menu::CreateToggle(const char* name, std::function<void()> func)
	{
		this->widgets.push_back(std::make_unique<Toggle>(name, func));
	}
	void Menu::CreateSlider(const char* name, std::function<void()> func)
	{
		this->widgets.push_back(std::make_unique<Slider>(name, func));
	}
	void Menu::CreateDropdown(const char* text, std::vector<std::string>& list, std::function<void()> func)
	{
		this->widgets.push_back(std::make_unique<Dropdown>(list, text, func));
	}
	void Menu::CreateImage(const char* name)
	{
		this->widgets.push_back(std::make_unique<Image>(name));
	}
}
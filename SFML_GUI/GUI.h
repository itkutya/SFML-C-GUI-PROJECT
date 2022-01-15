#pragma once

namespace GUI
{
	struct Color
	{
		int r = 0, g = 0, b = 0, a = 0;
	};
	/*-----------------------------------------Main class---------------------------------------------------------*/
	class Widgets : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual void update(const sf::Vector2f& mousePos, sf::Event& event) = 0;

		std::vector<std::unique_ptr<sf::RectangleShape>> m_shapes;
		std::vector<std::unique_ptr<sf::Color>> m_backgrounds;
		std::vector<std::unique_ptr<sf::Text>> m_texts;
		std::vector<std::unique_ptr<bool>> m_states;
		bool m_pressed = false;
		sf::Font m_font;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};
	/*-------------------------------------------Button---------------------------------------------------------*/
	class Button : public Widgets
	{
	public:
		Button();
		virtual ~Button();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const bool onButtonClick(unsigned short int index);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Toggle---------------------------------------------------------*/
	class Toggle : public Widgets
	{
	public:
		Toggle();
		virtual ~Toggle();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const bool getState(unsigned short int index);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Slider---------------------------------------------------------*/
	class Slider : public Widgets
	{
	public:
		Slider();
		virtual ~Slider();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const float getValue(unsigned short int index);
	private:
		std::vector<std::unique_ptr<sf::RectangleShape>> current_values;
		std::vector<std::unique_ptr<float>> m_values;
		std::vector<std::unique_ptr<std::string>> m_string;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*----------------------------------------Dropwdown-------------------------------------------------------*/
	class Dropdown : public Widgets
	{
	public:
		Dropdown(std::vector<std::string>& list);
		virtual ~Dropdown();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const int getActiveElement();

		short int scrool = 0;
	private:
		std::vector<std::unique_ptr<sf::Text>> active_text;
		std::vector<std::unique_ptr<sf::RectangleShape>> m_elements;
		std::vector<std::unique_ptr<sf::Color>> backgrounds;
		std::vector<std::unique_ptr<sf::Text>> m_options;
		std::vector<std::unique_ptr<std::string>> m_list;
		int active_element = 0;
		bool show_list = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
}
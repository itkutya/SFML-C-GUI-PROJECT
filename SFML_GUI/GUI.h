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

		std::string m_type;
		sf::RectangleShape m_shape;
		sf::Color m_background;
		sf::Text m_text;
		bool m_pressed = false;
		std::function<void()> function;

		int m_state = 0;

		short int scrool = 0;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};
	/*-------------------------------------------Button---------------------------------------------------------*/
	class Button : public Widgets
	{
	public:
		Button(const char* name, std::function<void()> func, sf::Font& font);
		virtual ~Button();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Toggle---------------------------------------------------------*/
	class Toggle : public Widgets
	{
	public:
		Toggle(const char* name, std::function<void()> func, sf::Font& font);
		virtual ~Toggle();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Slider---------------------------------------------------------*/
	class Slider : public Widgets
	{
	public:
		Slider(const char* name, std::function<void()> func, sf::Font& font);
		virtual ~Slider();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		sf::RectangleShape c_shape;
		sf::Text c_text;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*----------------------------------------Dropwdown-------------------------------------------------------*/
	class Dropdown : public Widgets
	{
	public:
		Dropdown(std::vector<std::string>& list, const char* name, std::function<void()> func, sf::Font& font);
		virtual ~Dropdown();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		sf::Text a_text;
		bool show_list;

		std::vector<sf::RectangleShape> c_elements;
		std::vector<sf::Color> c_backgrounds;
		std::vector<sf::Text> c_options;
		std::vector<std::string> c_list;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-------------------------------------------Image--------------------------------------------------------*/
	class Image : public Widgets
	{
	public:
		Image(const char* name, sf::Font& font);
		virtual ~Image();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		sf::Texture m_texture;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-------------------------------------------Menu--------------------------------------------------------*/
	class Menu : public sf::Drawable, public sf::Transformable
	{
	public:
		Menu();
		virtual ~Menu();

		std::vector<std::unique_ptr<Widgets>> widgets;
		std::vector<std::unique_ptr<int>> it;

		void update(const sf::Vector2f& mousePos, sf::Event& event);

		const int getVersion();

		void CreateButton(const char* name, std::function<void()> func);
		void CreateToggle(const char* name, std::function<void()> func);
		void CreateSlider(const char* name, std::function<void()> func);
		void CreateDropdown(const char* text, std::vector<std::string>& list, std::function<void()> func);
		void CreateImage(const char* name);

		const int getState(const char* name);
	private:
		sf::Font m_font;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
}
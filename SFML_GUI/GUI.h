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

		std::unique_ptr<sf::RectangleShape> m_shape;
		std::unique_ptr<sf::Color> m_background;
		std::unique_ptr<sf::Text> m_text;
		std::unique_ptr<bool> m_state;
		std::unique_ptr<bool> m_pressed;
		std::unique_ptr<sf::Font> m_font;
		std::function<void()> function;

		short int scrool = 0;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};
	/*-------------------------------------------Button---------------------------------------------------------*/
	class Button : public Widgets
	{
	public:
		Button(const char* name, std::function<void()> func);
		virtual ~Button();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Toggle---------------------------------------------------------*/
	class Toggle : public Widgets
	{
	public:
		Toggle(const char* name, std::function<void()> func);
		virtual ~Toggle();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const bool getState();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-----------------------------------------Slider---------------------------------------------------------*/
	class Slider : public Widgets
	{
	public:
		Slider(const char* name, std::function<void()> func);
		virtual ~Slider();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
		
		std::unique_ptr<std::string> c_string;

		const float getValue();
	private:
		std::unique_ptr<sf::RectangleShape> c_shape;
		std::unique_ptr<float> c_value;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*----------------------------------------Dropwdown-------------------------------------------------------*/
	class Dropdown : public Widgets
	{
	public:
		Dropdown(std::vector<std::string>& list, const char* name, std::function<void()> func);
		virtual ~Dropdown();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;

		const int getActiveElement();
	private:
		std::unique_ptr<sf::Text> a_text;
		std::unique_ptr<int> a_element;
		std::unique_ptr<bool> show_list;

		std::vector<std::unique_ptr<sf::RectangleShape>> c_elements;
		std::vector<std::unique_ptr<sf::Color>> c_backgrounds;
		std::vector<std::unique_ptr<sf::Text>> c_options;
		std::vector<std::unique_ptr<std::string>> c_list;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-------------------------------------------Image--------------------------------------------------------*/
	class Image : public Widgets
	{
	public:
		Image(const char* name);
		virtual ~Image();

		void update(const sf::Vector2f& mousePos, sf::Event& event) override;
	private:
		std::unique_ptr<sf::Texture> m_texture;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
	/*-------------------------------------------Menu--------------------------------------------------------*/
	class Menu : public sf::Drawable, public sf::Transformable
	{
	public:
		Menu();
		virtual ~Menu();

		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<std::unique_ptr<Toggle>> toggles;
		std::vector<std::unique_ptr<Slider>> sliders;
		std::vector<std::unique_ptr<Dropdown>> dropdowns;
		std::vector<std::unique_ptr<Image>> images;

		void update(const sf::Vector2f& mousePos, sf::Event& event);

		const float getVersion();

		void CreateButton(const char* name, std::function<void()> func);
		void CreateToggle(const char* name, std::function<void()> func);
		void CreateSlider(const char* name, std::function<void()> func);
		void CreateDropdown(const char* text, std::vector<std::string>& list, std::function<void()> func);
		void CreateImage(const char* name);

		const int getActiveElement(const char* name);
		const float getValue(const char* name);
		const bool getState(const char* name);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
	};
}
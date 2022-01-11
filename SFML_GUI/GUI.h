#pragma once

namespace GUI
{
	class Widgets : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual void update(const sf::Vector2f& mousePos, sf::Event& event) = 0;

		std::vector<sf::RectangleShape> m_shapes;
		std::vector<sf::Color> m_backgrounds;
		std::vector<sf::Text> m_texts;
		std::vector<bool> m_states;
		bool m_pressed = false;
		sf::Font m_font;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};

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
}